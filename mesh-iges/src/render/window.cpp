#include "window.h"
#include "CGridSceneNode.h"
#include "../iges/CIGSMeshLoader.h"

Window::Window() noexcept : Igs{0}, loaded(nullptr), renderAabbox(false)
{
	irr::SIrrlichtCreationParameters cp;
        cp.AntiAlias = 4;
        cp.Bits = 32;
        cp.DriverType = irr::video::EDT_OPENGL;
        cp.Vsync = true;
        cp.WindowSize = irr::core::dimension2d<irr::u32>(800, 600);
	device = irr::createDeviceEx(cp);
    device->setWindowCaption(L"IGES(*.ics/*.igs) Loader sample");

    driver = device->getVideoDriver();
    guienv = device->getGUIEnvironment();
    filesys = device->getFileSystem();
    smgr = device->getSceneManager();
    device->setEventReceiver(this);

    mat[0].setTexture(0, driver->getTexture("point.png"));
    mat[1].setTexture(0, driver->getTexture("line.png"));
    mat[2].setTexture(0, driver->getTexture("geometry.png"));
    mat[3].setTexture(0, driver->getTexture("geometry.png"));

    mat[0].Thickness = 50.f;
    mat[1].Thickness = 1.f;
    mat[0].MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
    mat[1].MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
    mat[3].MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
    mat[0].Lighting = mat[1].Lighting = mat[2].Lighting = mat[3].Lighting = mat[4].Lighting = false;

    smgr->addExternalMeshLoader(new irr::scene::CIGSMeshLoader());
    smgr->addCameraSceneNodeMaya();

    gridSceneNode = new irr::scene::CGridSceneNode(smgr->getRootSceneNode(), smgr, -1, 1);
    gridSceneNode->drop();

    guienv->addButton({350, 5, 450, 20}, 0, 1, L"Load *.Igs/*.igs mesh");
    guienv->addStaticText(
        L"b -> toggle bounding box\n"
        L"g -> toggle grid",
        {0, 0, 250, 20}
    );
}

Window::~Window() noexcept
{
    device->drop();
}

bool Window::OnEvent(const irr::SEvent &ev) noexcept
{
    if(ev.EventType == irr::EET_KEY_INPUT_EVENT  && !ev.KeyInput.PressedDown)
    {
        if(ev.KeyInput.Key == irr::KEY_KEY_B)
            renderAabbox = !renderAabbox;
        if(ev.KeyInput.Key == irr::KEY_KEY_G)
            gridSceneNode->setVisible(!gridSceneNode->isVisible());
    }
    if(ev.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = ev.GUIEvent.Caller->getID();
        switch(ev.GUIEvent.EventType)
        {
            case irr::gui::EGET_BUTTON_CLICKED:
                // test needed else it can be appening
                // with FileOpenDialog when no file is selected
                if(id ==  1)
                    file = guienv->addFileOpenDialog(L"Load *.Igs/*.igs mesh");
            break;
            case irr::gui::EGET_FILE_SELECTED:
                if(irr::core::hasFileExtension(file->getFileName(), "Igs") ||
                   irr::core::hasFileExtension(file->getFileName(), "igs"))
                {
                    if(loaded)
                    {
                        loaded->drop();
                        loaded = nullptr;
                    }

                    loaded = smgr->getMesh(file->getFileName());

                    if(loaded)
                    {
                        loaded->grab();

                        for(int j = 0; j<3; ++j)
                        {
                            Igs[j] = loaded->getMesh(j);
                            Igs[j]->setHardwareMappingHint(
                                irr::scene::EHM_STATIC,
                                irr::scene::EBT_VERTEX_AND_INDEX
                            );
                        }

                        irr::core::vector3df target =
                            loaded->getBoundingBox().getCenter();

                        smgr->getActiveCamera()->setPosition(target);
                        smgr->getActiveCamera()->setTarget(target);
                    }
                }
                else
                {
                    irr::core::stringw tmp;
                        tmp += L"the selected file \"";
                        tmp += file->getFileName();
                        tmp += L"\" must have an Igs extention";
                    guienv->addMessageBox(L"incorrect file extention", tmp.c_str());
                }
            break;
        }
    }
    return false;
}

void Window::run() noexcept
{
    while(device->run())
    {
        driver->beginScene(true, true, {255,100,101,140});
        smgr->drawAll();

        for(int j = 0; j<irr::scene::IGS_COUNT; ++j)
        {
            if(Igs[j])
            {
                driver->setMaterial(mat[j]);
                for(int i = 0; i<Igs[j]->getMeshBufferCount(); ++i)
                {
                    driver->drawVertexPrimitiveList(
                        Igs[j]->getMeshBuffer(i)->getVertices(),
                        Igs[j]->getMeshBuffer(i)->getVertexCount(),
                        Igs[j]->getMeshBuffer(i)->getIndices(),
                        Igs[j]->getMeshBuffer(i)->getIndexCount()/(j+1),
                        irr::video::EVT_STANDARD,
                        irr::scene::igs_render_mesh_buffer[j]
                    );
                }
            }
        }

        driver->setMaterial(mat[4]);

        if(loaded && renderAabbox)
            driver->draw3DBox(loaded->getBoundingBox(), {255, 255, 0, 0});

        guienv->drawAll();
        driver->endScene();
    }
}

