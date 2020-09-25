#include "flowmap.h"

FlowMap::FlowMap(irr::video::IVideoDriver *i, irr::core::dimension2du dim)
    : driver(i), obstruction(nullptr), source(nullptr), nextUpdate(true)
{
    rtt = driver->addRenderTargetTexture(dim, "env", irr::video::ECF_G16R16F);
}

FlowMap::~FlowMap()
{
    rtt->drop();
}

void FlowMap::setObstructionMap(irr::video::ITexture *i)
{
    if(obstruction) obstruction->drop();
    obstruction = i;
    if(obstruction) obstruction->grab();
}

irr::video::ITexture* FlowMap::getObstructionMap()
{
    return obstruction;
}

void FlowMap::setPersistentWaveSource(irr::video::ITexture *i)
{
    if(source) source->drop();
    source = i;
    if(source) source->grab();
}

irr::video::ITexture* FlowMap::getPersistentWaveSource()
{
    return source;
}

irr::video::ITexture* FlowMap::getRTT()
{
    return rtt;
}

void FlowMap::update()
{
    // render twice
    //    one frame for the temporary sources
    //    one frame to clean it

    if(nextUpdate || frameSource.size() || frameObstruction.size())
    {
        driver->setRenderTarget(rtt, nextUpdate*irr::video::ECBF_COLOR);

        for(int i = 0; i<frameObstruction.size(); ++i)
            driver->draw2DLine(frameObstruction[i].start, frameObstruction[i].end, {255, 255, 0, 0});
        frameObstruction.clear();

        for(int i = 0; i<frameSource.size(); ++i)
            driver->draw2DLine(frameSource[i].start, frameSource[i].end, {255, 0, 255, 0});
        frameSource.clear();

        driver->setRenderTarget(nullptr, irr::video::ECBF_NONE);
        nextUpdate = false;
    }
}
