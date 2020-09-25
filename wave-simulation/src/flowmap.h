#ifndef FLOWMAP_H
#define FLOWMAP_H

#include <irrlicht.h>

/**
 * used to render ObstructionMap & SourceMap(wave)
 * using ECF_G16R16F
 *      r = ObstructionMap
 *      g = SourceMap
 **/
class FlowMap
{
    public:
        FlowMap(irr::video::IVideoDriver*, irr::core::dimension2du);
        virtual ~FlowMap();

        irr::core::array<irr::core::line2di> frameObstruction;
        irr::core::array<irr::core::line2di> frameSource;

        virtual void setObstructionMap(irr::video::ITexture*);
        virtual irr::video::ITexture* getObstructionMap();

        virtual void setPersistentWaveSource(irr::video::ITexture*);
        virtual irr::video::ITexture* getPersistentWaveSource();

        virtual irr::video::ITexture* getRTT();

        void update();
    protected:
        irr::video::IVideoDriver *driver;
        irr::video::ITexture *rtt;
        irr::video::ITexture *source;
        irr::video::ITexture *obstruction;
    private:
        bool nextUpdate;
};

#endif // FLOWMAP_H
