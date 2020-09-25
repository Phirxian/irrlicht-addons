#include "datacomputation.h"

#define Z_FIGHT 0.00001f

DataComputation::DataComputation(irr::video::IVideoDriver *video, irr::video::ITexture *i) : driver(video), input(i)
{
    screenVertices[0] = {-1.f,  1.f, Z_FIGHT, 0.f, 0.f, 1.f, {255,255,255,255}, 0.f, 0.f};
    screenVertices[1] = { 1.f,  1.f, Z_FIGHT, 0.f, 0.f, 1.f, {255,255,255,255}, 1.f, 0.f};
    screenVertices[2] = { 1.f, -1.f, Z_FIGHT, 0.f, 0.f, 1.f, {255,255,255,255}, 1.f, 1.f};
    screenVertices[3] = {-1.f, -1.f, Z_FIGHT, 0.f, 0.f, 1.f, {255,255,255,255}, 0.f, 1.f};

    screenIndices[0] = 0;
    screenIndices[1] = 1;
    screenIndices[2] = 2;
    screenIndices[3] = 3;

    data = driver->addRenderTargetTexture(i->getOriginalSize(), "data", irr::video::ECF_G32R32F);
    vd = new VerticalDerivative(driver, data, i);

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
        "uniform float gravity;                                             \n"
        "uniform float alpha;                                               \n"
        "uniform float dt;                                                  \n"
        "                                                                   \n"
        "void main()                                                        \n"
        "{                                                                  \n"
        "    vec4 color = texture2D(texture[1], gl_TexCoord[0].xy);         \n"
        "         color.r *= texture2D(texture[0], gl_TexCoord[0].xy).r;    \n"
        "                                                                   \n"
        "    float adt = alpha*dt;                                          \n"
        "    float adt2 = 1.0/(1.0+adt);                                    \n"
        "    float vd = texture2D(texture[2], gl_TexCoord[0].xy).r;         \n"
        "                                                                   \n"
        "    gl_FragData[0].g = color.r;                                    \n"
        "    gl_FragData[0].r = color.r*(2.0-adt)-color.g-gravity*vd;       \n"
        "    gl_FragData[0].r *= adt2;                                      \n"
        "    gl_FragData[0].r += texture2D(texture[0], gl_TexCoord[0].xy).g;\n"
        "    gl_FragData[0].r *= texture2D(texture[0], gl_TexCoord[0].xy).r;\n"
        "}                                                                  \n"
        "                                                                   \n"
    ;

    dt = 0.03;
    alpha = 0.3;
    gravity = 9.8 * dt * dt;

    scrm.MaterialType = (irr::video::E_MATERIAL_TYPE)
        driver->getGPUProgrammingServices()->addHighLevelShaderMaterial(
            vs, "main", irr::video::EVST_VS_2_0, ps, "main", irr::video::EPST_PS_2_0,
            this, irr::video::E_MATERIAL_TYPE::EMT_SOLID
        );
    scrm.setTexture(0, i);
    scrm.setTexture(1, getRTT());
    scrm.setTexture(2, vd->getRTT());
}

DataComputation::~DataComputation()
{
    data->drop();
}

void DataComputation::OnSetConstants(irr::video::IMaterialRendererServices *service, irr::s32 userData) noexcept
{
    irr::s32 id;
    static const irr::s32 texture[] = {0, 1, 2, 3};

    id = service->getPixelShaderConstantID("texture");
    service->setPixelShaderConstant(id, (irr::s32*)texture, 4);

    id = service->getPixelShaderConstantID("gravity");
    service->setPixelShaderConstant(id, &gravity, 1);

    id = service->getPixelShaderConstantID("alpha");
    service->setPixelShaderConstant(id, &alpha, 1);

    id = service->getPixelShaderConstantID("dt");
    service->setPixelShaderConstant(id, &dt, 1);
}

VerticalDerivative* DataComputation::getVerticalDerivative()
{
    return vd;
}

irr::video::ITexture* DataComputation::getRTT()
{
    return data;
}

void DataComputation::render()
{
    // compute vertical derivative
    vd->render();

    driver->setRenderTarget(data, irr::video::ECBF_NONE);

    driver->setTransform(irr::video::ETS_PROJECTION, irr::core::IdentityMatrix);
    driver->setTransform(irr::video::ETS_VIEW, irr::core::IdentityMatrix);
    driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);

    driver->setMaterial(scrm);

    driver->drawVertexPrimitiveList(
        screenVertices, 4, screenIndices, 1,
        irr::video::EVT_STANDARD, irr::scene::EPT_QUADS
    );

    driver->setRenderTarget(nullptr, irr::video::ECBF_NONE);
}
