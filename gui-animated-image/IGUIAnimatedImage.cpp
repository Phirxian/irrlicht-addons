#include "IGUIAnimatedImage.h"

#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/ITimer.h>
#include <irrlicht/IImage.h>

namespace irr
{
    namespace gui
    {
        IGUIAnimatedImage::IGUIAnimatedImage(IGUIEnvironment *environment, ITimer *time, IGUIElement *parent, s32 id)
            : IGUIElement(EGUIET_IMAGE, environment, parent, id, core::recti()),
              current_frame(0), speed(0.2f), clr(0xffffffff), timer(time)
        {
        }
        IGUIAnimatedImage::~IGUIAnimatedImage()
        {
            clearFrame();
        }
        /**************************************************************/
        void IGUIAnimatedImage::makeWithSprite(char*txt,int numberFrame,int state,int whidth,int height,int interval)
        {
            video::IImage *image = Environment->getVideoDriver()->createImageFromFile(txt);
            for(int i=0; i<numberFrame; ++i)
            {
                video::IImage *new_frame = Environment->getVideoDriver()->createImage(video::ECF_A8R8G8B8,core::dimension2du(whidth,height));
                core::stringw name = "IGUIAnimatedImage_"; name += state; name += "_"; name += numberFrame;
                new_frame->fill({255,255,255,255});

                for(char x = 0; x < whidth; ++x)
                {
                    for(char y = 0; y < height; ++y)
                    {
                        new_frame->setPixel(x, y, image->getPixel(1+(i*(whidth+1))+x, 1+(state*(height+1))+y));
                    }
                }

                addFrame(Environment->getVideoDriver()->addTexture(name.c_str(),new_frame));
            }
        }
        /**************************************************************/
        void IGUIAnimatedImage::addFrame(video::ITexture*frm)
        {
            frm->grab();
            frames.push_back(frm);
        }
        void IGUIAnimatedImage::removeFrame(int i)
        {
            frames[i]->drop();
            frames.erase(i);
        }
        void IGUIAnimatedImage::insertFrame(int i,video::ITexture*frm)
        {
            frm->grab();
            frames.insert(frm,i);
        }
        void IGUIAnimatedImage::clearFrame()
        {
            while(frames.size())
                removeFrame(0);
        }
        /**************************************************************/
        void IGUIAnimatedImage::setSpeed(f32 f)
        {
            speed = f;
        }
        f32 IGUIAnimatedImage::getSpeed()
        {
            return speed;
        }
        void IGUIAnimatedImage::setColor(video::SColor s)
        {
            clr = s;
        }
        video::SColor IGUIAnimatedImage::getColor()
        {
            return clr;
        }
        video::ITexture* IGUIAnimatedImage::operator[](u32 i)
        {
            return frames[i];
        }
        video::ITexture* IGUIAnimatedImage::getFrame(u32 i)
        {
            return frames[i];
        }
        video::ITexture** IGUIAnimatedImage::getArray()
        {
            return frames.pointer();
        }
        /**************************************************************/
        void IGUIAnimatedImage::draw()
        {
            if(frames.size() > current_frame && frames[current_frame])
            {
                core::recti ImageRect(core::position2di(), frames[current_frame]->getSize());
                Environment->getVideoDriver()->draw2DImage(frames[current_frame], AbsoluteRect.UpperLeftCorner, ImageRect, 0, clr, true);
            }
            if(timer->getTime() - lastTime > speed*1000)
            {
                if (++current_frame == frames.size())
                    current_frame = 0;
                lastTime = timer->getTime();
            }
        }
    }
}
