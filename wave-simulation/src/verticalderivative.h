#ifndef VERTICALDERIVATIVE_H
#define VERTICALDERIVATIVE_H

#include <irrlicht.h>

/**
 * used to generate the wave map
 * render a bump texture for scene node
 * using ECF_A32B32G32R32F
 *      a = display map
 *      r = height
 *      g = previous height
 *      b = vertical derivative
 */
class VerticalDerivative : public irr::video::IShaderConstantSetCallBack
{
    public:
        VerticalDerivative(irr::video::IVideoDriver*, irr::video::ITexture *height, irr::video::ITexture *flowmap);
        virtual ~VerticalDerivative();

        virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData) noexcept;

        irr::video::ITexture* getRTT();

        void render();
    protected:
        float kernel[13][13];
        irr::video::ITexture *flowmap;
        irr::video::ITexture *height;
    private:
        irr::u16 screenIndices[4];
        irr::video::S3DVertex screenVertices[4];
        irr::video::SMaterial scrm;

        irr::video::ITexture *data;
        irr::video::IVideoDriver *driver;
};

#endif // VerticalDerivative_H
