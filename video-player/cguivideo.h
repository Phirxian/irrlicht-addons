#ifndef _CGUI_VIDEO_H_
#define _CGUI_VIDEO_H_

#include "svideo.h"

#if defined SDL_SUPPORT || defined SDL_AUDIO_SUPPORT
    #include <SDL.h>
    #include <SDL_audio.h>
    #define SDL_AUDIO_SUPPORT
#endif

#if defined IRRLICHT_SUPPORT
    #include <irrlicht/irrlicht.h>
#endif

/**                                 * * * * * * * * * * * * * * * * * * * * * * * * *                                    **/
/**                                 *                                               *                                    **/
/**                                 *           created by Ovan or Magun            *                                    **/
/**                                 *   compile with : lavformat,lavcodec,lavutil   *                                    **/
/**                                 *        and other library defined last         *                                    **/
/**                                 *                                               *                                    **/
/**                                 *                 conctact me :                 *                                    **/
/**                                 *                www.irrlicht.fr                *                                    **/
/**                                 *            www.immortal-galaxy.com            *                                    **/
/**                                 *                                               *                                    **/
/**                                 * * * * * * * * * * * * * * * * * * * * * * * * *                                    **/

namespace interne
{
    namespace graphic
    {
        class CGUIVideo
        {
            public:
                #if defined SDL_SUPPORT
                    CGUIVideo(SVideo*,bool run = true,bool loop = false);
                    virtual bool draw(SDL_Surface *screen, SDL_Rect rect);
                #elif defined IRRLICHT_SUPPORT
                    CGUIVideo(irr::video::IVideoDriver*drive, irr::ITimer *time, SVideo*,bool run = true,bool loop = false);
                #endif

                virtual ~CGUIVideo();

                virtual bool refresh();// no limit refresh video
                virtual bool refreshByTime();//limit refresh by time
                virtual bool refreshByFPS();//sync video fps and window fps for slow computer or slow render window ... unfinished

                virtual void setFPS(double fps);//set the video decoding frame rate, if !fps => fps = video.fps (used with refreshByFPS)

                #if defined SDL_SUPPORT
                    virtual bool draw(SDL_Surface *screen, SDL_Rect rect);
                #elif defined IRRLICHT_SUPPORT
                    virtual irr::video::ITexture *getTexture();
                    virtual irr::video::ITexture *draw();
                #endif

                SVideo *getVideoData();
            protected:
                void WindowFPS();

                int lastTime, time, frame, io;
                #if defined SDL_SUPPORT
                    SDL_Overlay *bmp;
                #elif defined IRRLICHT_SUPPORT
                    irr::ITimer *Timer;
                    irr::video::ITexture *VTexture;
                    irr::video::IVideoDriver*driver;
                #endif

                SVideo *data;
        };
    }
}
#endif // CGUIVideo_H
