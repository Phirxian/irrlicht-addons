#include "gameintro.h"

#include <iostream>

using namespace irr;
using namespace video;
using namespace core;

namespace interne
{
    namespace graphic
    {
        GameIntro::GameIntro(irr::IrrlichtDevice*dev, const std::string & video_file, bool rsz) : device(dev)
        {
            current_render_size = device->getVideoDriver()->getScreenSize();
            resize_for_render = rsz;

            device->getVideoDriver()->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, false);
            if(!vi.open(video_file.c_str(), true)) throw "Can't open video file";
            vi.play(true);

            intro = new CGUIVideo(device->getVideoDriver(), device->getTimer(), &vi);

            rect<s32> size(0,0,vi.getWidth(), vi.getHeight());
            if(resize_for_render) device->getVideoDriver()->setViewPort(size);
        }
        GameIntro::~GameIntro()
        {
            delete intro;
            rect<s32> size(position2d<s32>(0,0),current_render_size);
            if(resize_for_render) device->getVideoDriver()->OnResize(current_render_size);
            if(resize_for_render) device->getVideoDriver()->setViewPort(size);
            device->getVideoDriver()->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, true);
        }
        bool GameIntro::externalEvent(SEvent event)
        {
            if(event.EventType == EET_MOUSE_INPUT_EVENT && event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP && intro)
            {
                return true;
            }
            if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown == false && intro)
            {
                switch(event.KeyInput.Key)
                {
                    case KEY_ESCAPE: case KEY_DELETE: case KEY_RETURN: case KEY_SPACE:
                    return true; break; default: break;
                }
            }
            return false;
        }
        bool GameIntro::draw()
        {
            if(intro && intro->refreshByTime() && device->run())
            {
                device->getVideoDriver()->draw2DImage(intro->draw(), position2d<s32>(0, 0));
                return false;
            }
            device->getVideoDriver()->draw2DImage(intro->draw(), position2d<s32>(0, 0));
            return true;
        }
    }
}
