#ifndef _I_GUI_ANIMATED_IMAGE_
#define _I_GUI_ANIMATED_IMAGE_

/**         * * * * * * * * * * * * * * * * * * * * * * * * *         **/
/**         *                                               *         **/
/**         *           created by Ovan or Magun            *         **/
/**         *                                               *         **/
/**         *                 conctact me :                 *         **/
/**         *                www.irrlicht.fr                *         **/
/**         *            irrlicht.sourceforge.net           *         **/
/**         *                                               *         **/
/**         * * * * * * * * * * * * * * * * * * * * * * * * *         **/

#include <irrlicht/IGUIElement.h>

namespace irr
{
    class IrrlichtDevice;
    class ITimer;
    
    namespace gui
    {
        class IGUIAnimatedImage : public IGUIElement
        {
            public:
                IGUIAnimatedImage(IGUIEnvironment *environment,
                                  ITimer *timer,
                                  IGUIElement *parent = 0,
                                  s32 id = -1);
                virtual ~IGUIAnimatedImage();

                void makeWithSprite(char*, int nbFrame, int state, int width, int height, int interval);

                void addFrame(video::ITexture*);
                void insertFrame(int, video::ITexture*);
                void removeFrame(int);
                void clearFrame();

                void setSpeed(f32);
                void setColor(video::SColor s);

                f32 getSpeed();
                video::SColor getColor();

                video::ITexture*  operator[](u32 i);
                video::ITexture*  getFrame  (u32 i);
                video::ITexture** getArray();

                virtual void draw();
            protected:
                unsigned short int current_frame;
                f32 lastTime, speed;

                video::SColor clr;
                core::array<video::ITexture*> frames;

                ITimer *timer;
            private:
        };
    }
}

#endif // IANIMATEDIMAGE_H
