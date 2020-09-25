#include "verticalderivative.h"

#define Z_FIGHT 0.00001f


VerticalDerivative::VerticalDerivative(irr::video::IVideoDriver *video, irr::video::ITexture *h, irr::video::ITexture *f) : driver(video), height(h), flowmap(f)
{
    screenVertices[0] = {-1.f,  1.f, Z_FIGHT, 0.f, 0.f, 1.f, {255,255,255,255}, 0.f, 0.f};
    screenVertices[1] = { 1.f,  1.f, Z_FIGHT, 0.f, 0.f, 1.f, {255,255,255,255}, 1.f, 0.f};
    screenVertices[2] = { 1.f, -1.f, Z_FIGHT, 0.f, 0.f, 1.f, {255,255,255,255}, 1.f, 1.f};
    screenVertices[3] = {-1.f, -1.f, Z_FIGHT, 0.f, 0.f, 1.f, {255,255,255,255}, 0.f, 1.f};

    screenIndices[0] = 0;
    screenIndices[1] = 1;
    screenIndices[2] = 2;
    screenIndices[3] = 3;

    data = driver->addRenderTargetTexture(h->getOriginalSize(), "data", irr::video::ECF_R32F);

    const char *vs =
        "void main()"
        "{"
        "   gl_TexCoord[0] = gl_MultiTexCoord0;"
        "   gl_Position = ftransform();"
        "   gl_FrontColor = gl_Color;"
        "}"
    ;

    /*
     * height in rtt.r
     * previous height in rtt.g
     * vertical derivativ in rtt.b
     * display in rtt.a
     *
     * obstruction in flowmap.r
     * source in flowmap.g
     */

    const char *ps =
        "uniform float kernel[13][13];                                      \n"
        "uniform sampler2D texture[2];                                      \n"
        "                                                                   \n"
        "void main()                                                        \n"
        "{                                                                  \n"
        "    float vd = 0;                                                  \n"
        "    for(int iix=-6;iix<=6;iix++)                                   \n"
        "    {                                                              \n"
        "       for(int iiy=-6;iiy<=6;iiy++)                                \n"
        "       {                                                           \n"
        "           vec2 coord = gl_TexCoord[0].xy+vec2(iix, iiy);          \n"
        "           float h = texture2D(texture[0], coord).r;               \n"
        "                 h *= texture2D(texture[1], coord).r;              \n"
        "           vd += kernel[iix+6][iiy+6] * h;                         \n"
        "       }                                                           \n"
        "    }                                                              \n"
        "    gl_FragColor = vd;                                             \n"
        "}                                                                  \n"
        "                                                                   \n"
    ;

    scrm.MaterialType = (irr::video::E_MATERIAL_TYPE)
        driver->getGPUProgrammingServices()->addHighLevelShaderMaterial(
            vs, "main", irr::video::EVST_VS_2_0, ps, "main", irr::video::EPST_PS_2_0,
            this, irr::video::E_MATERIAL_TYPE::EMT_SOLID
        );
    scrm.setTexture(0, height);
    scrm.setTexture(1, flowmap);

    // initializeKernel()

    double dk = 0.01;
    double sigma = 1.0;
    double norm = 0;

    for(double k=0;k<10;k+=dk)
        norm += k*k*exp(-sigma*k*k);

    for( int i=-6;i<=6;i++ )
    {
        for( int j=-6;j<=6;j++ )
        {
            double r = sqrt( (float)(i*i + j*j) );
            double kern = 0;

            for( double k=0;k<10;k+=dk)
                kern += k*k*exp(-sigma*k*k)*j0(r*k);

            kernel[i+6][j+6] = kern / norm;
        }
    }
}

VerticalDerivative::~VerticalDerivative()
{
    data->drop();
}

void VerticalDerivative::OnSetConstants(irr::video::IMaterialRendererServices *service, irr::s32 userData) noexcept
{
    irr::s32 id;
    static const irr::s32 texture[] = {0, 1, 2, 3};

    id = service->getPixelShaderConstantID("kernel");
    service->setPixelShaderConstant(id, (irr::f32*)&kernel, 13*13);

    id = service->getPixelShaderConstantID("input");
    service->setPixelShaderConstant(id, (irr::s32*)&texture, 4);
}

irr::video::ITexture* VerticalDerivative::getRTT()
{
    return data;
}

void VerticalDerivative::render()
{
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
