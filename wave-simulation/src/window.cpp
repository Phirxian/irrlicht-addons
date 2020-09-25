#include "window.h"

Window::Window() noexcept : cursor{0, 0}, scaling(1.f), size{512.f, 512.f}
{
	irr::SIrrlichtCreationParameters cp;
        cp.AntiAlias = 4;
        cp.Bits = 32;
        cp.DriverType = irr::video::EDT_OPENGL;
        cp.Vsync = true;
        cp.WindowSize = irr::core::dimension2du(800, 600);
	device = irr::createDeviceEx(cp);
    device->setWindowCaption(L"water simulation trought gpu");

    driver = device->getVideoDriver();
    guienv = device->getGUIEnvironment();
    filesys = device->getFileSystem();
    smgr = device->getSceneManager();
    device->setEventReceiver(this);

    if(!driver->queryFeature(irr::video::EVDF_RENDER_TO_TARGET) ||
       !driver->queryFeature(irr::video::EVDF_PIXEL_SHADER_2_0))
    {
        printf("graphic card won't support RTT or GLSL 2.0\n");
        device->drop();
        exit(1);
    }

    map = new FlowMap(driver, {(irr::u32)size.Width, (irr::u32)size.Height});
    cmp = new DataComputation(driver, map->getRTT());

    irr::video::SMaterial tmp;

    floor = smgr->addMeshSceneNode(smgr->addHillPlaneMesh("floor", size, {1, 1}, &tmp));
    floor->getMaterial(0).setTexture(0, driver->getTexture("stones.jpg"));
	floor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	floor->getMaterial(0).getTextureMatrix(0).setTextureScale(2.f, 2.f);

    water = smgr->addMeshSceneNode(smgr->addHillPlaneMesh("water", size, {1, 1}, &tmp));
	water->setMaterialType(buildShader(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL));
	water->setMaterialFlag(irr::video::EMF_BLEND_OPERATION, true);
	water->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    water->setPosition({0.f, 10.f, 0.f});

    water->getMaterial(0).setTexture(3, driver->getTexture("water.jpg"));
    water->getMaterial(0).setTexture(2, cmp->getVerticalDerivative()->getRTT());
    water->getMaterial(0).setTexture(1, cmp->getRTT());
    water->getMaterial(0).setTexture(0, map->getRTT());

	auto selector = smgr->createTriangleSelectorFromBoundingBox(water);
	water->setTriangleSelector(selector);
	selector->drop();

    smgr->addCameraSceneNodeMaya();
}

Window::~Window() noexcept
{
    device->drop();
    delete map;
    delete cmp;
}

irr::video::E_MATERIAL_TYPE Window::buildShader(irr::video::E_MATERIAL_TYPE base)
{
    const char *vs =
        "void main()"
        "{"
        "   gl_TexCoord[0] = gl_MultiTexCoord0;"
        "   gl_Position = ftransform();"
        "   gl_FrontColor = gl_Color;"
        "}"
    ;

    const char *ps =
        "uniform sampler2D texture[4];                                      \n"
        "uniform float scaling_factor;                                      \n"
        "                                                                   \n"
        "void main()                                                        \n"
        "{                                                                  \n"
        "   float height = texture2D(texture[1], gl_TexCoord[0].xy).r;      \n"
        "   float obstruction = texture2D(texture[0], gl_TexCoord[0].xy).r; \n"
        "   gl_FragColor = 0.5*(height/scaling_factor + 1.0)*obstruction;   \n"
        "   gl_FragColor.r = texture2D(texture[0], gl_TexCoord[0].xy).g;    \n"
        "   gl_FragColor.g = texture2D(texture[1], gl_TexCoord[0].xy).r;    \n"
        "   gl_FragColor.b = texture2D(texture[2], gl_TexCoord[0].xy).r;    \n"
        "   gl_FragColor.a = 0.5;                                           \n"
        "}                                                                  \n"
        "                                                                   \n"
    ;

    return (irr::video::E_MATERIAL_TYPE)
        driver->getGPUProgrammingServices()->addHighLevelShaderMaterial(
            vs, "main", irr::video::EVST_VS_2_0, ps, "main", irr::video::EPST_PS_2_0,
            this, base
        );
}

void Window::OnSetConstants(irr::video::IMaterialRendererServices *service, irr::s32 userData) noexcept
{
    irr::s32 texture[] = {0, 1, 2, 3};
    irr::s32 id = service->getPixelShaderConstantID("textures");
    service->setPixelShaderConstant(id, texture, 4);

    id = service->getPixelShaderConstantID("scaling_factor");
    service->setPixelShaderConstant(id, &scaling, 1);
}

bool Window::OnEvent(const irr::SEvent &ev) noexcept
{
    if(ev.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        restart[0] |= ev.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN;
        restart[1] |= ev.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN;
        cursor[0] = ev.MouseInput.isLeftPressed();
        cursor[1] = ev.MouseInput.isRightPressed();
    }
    if(ev.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        if(!ev.KeyInput.PressedDown && ev.KeyInput.Key == irr::KEY_ESCAPE)
        {
            smgr->getActiveCamera()->setInputReceiverEnabled(
                !smgr->getActiveCamera()->isInputReceiverEnabled()
            );
        }
    }
    return false;
}

void Window::run() noexcept
{
    while(device->run())
    {
        driver->beginScene(irr::video::ECBF_COLOR | irr::video::ECBF_DEPTH, {255,100,100,140});

        if(!smgr->getActiveCamera()->isInputReceiverEnabled() && (cursor[0] || cursor[1]))
        {
            auto pos = device->getCursorControl()->getPosition();
            auto ray = smgr->getSceneCollisionManager()->
                       getRayFromScreenCoordinates(pos, smgr->getActiveCamera());

            irr::core::vector3df outCollisionPoint;
            irr::core::triangle3df outTriangle;

            auto node = smgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
                ray, outCollisionPoint, outTriangle
            );

            if(node == water)
            {
                outCollisionPoint += {size.Width/2.f, 0.f, size.Height/2.f};

                if(cursor[0])
                {
                    if(restart[0])
                    {
                        line[0].end.set({(irr::s32)outCollisionPoint.X, (irr::s32)outCollisionPoint.Z});
                        restart[0] = false;
                    }

                    line[0].start = line[0].end;
                    line[0].end.set({(irr::s32)outCollisionPoint.X, (irr::s32)outCollisionPoint.Z});

                    map->frameSource.push_back(line[0]);
                }

                if(cursor[1])
                {
                    if(restart[1])
                    {
                        line[1].end.set({(irr::s32)outCollisionPoint.X, (irr::s32)outCollisionPoint.Z});
                        restart[1] = false;
                    }

                    line[1].start = line[1].end;
                    line[1].end.set({(irr::s32)outCollisionPoint.X, (irr::s32)outCollisionPoint.Z});

                    // obstruction map
                    map->frameObstruction.push_back(line[1]);
                }
            }
            else
                restart[0] = restart[1] = true;
        }

        map->update();
        cmp->render();

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
}

