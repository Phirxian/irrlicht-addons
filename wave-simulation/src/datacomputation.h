#ifndef DATACOMPUTATION_H
#define DATACOMPUTATION_H

#include <irrlicht.h>
#include "verticalderivative.h"

/**
 * used to generate the wave map
 * render a bump texture for scene node
 * using ECF_A32B32G32R32F
 *      a = display map
 *      r = height
 *      g = previous height
 *      b = vertical derivative
 */
class DataComputation : public irr::video::IShaderConstantSetCallBack
{
    public:
        DataComputation(irr::video::IVideoDriver*, irr::video::ITexture *flowmap);
        virtual ~DataComputation();

        virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData) noexcept;

        VerticalDerivative* getVerticalDerivative();

        irr::video::ITexture* getRTT();

        void render();
    protected:
        VerticalDerivative *vd;
        irr::video::IVideoDriver *driver;
        float dt, gravity, alpha;
    private:
        irr::u16 screenIndices[4];
        irr::video::S3DVertex screenVertices[4];
        irr::video::ITexture *data;
        irr::video::ITexture *input;
        irr::video::SMaterial scrm;
};

#endif // DATACOMPUTATION_H
