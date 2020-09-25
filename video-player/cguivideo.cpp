#include "cguivideo.h"

#include <iostream>

using namespace std;
#if defined WIN32 || defined WIN64 || defined _WIN32_ || defined _WIN64_
    extern "C"
    {
        #include <ffmpeg/avcodec.h>
    }
#else
    extern "C"
    {
       #include <libavcodec/avcodec.h>
    }
#endif

/** * * * * * * * * * * * * * * * * * * * * * * * * *
    *                                               *
    *           created by Ovan or Magun            *
    *   compile with : lavformat,lavcodec,lavutil   *
    *        and other library defined last         *
    *                                               *
    *                 conctact me :                 *
    *                www.irrlicht.fr                *
    *            www.immortal-galaxy.com            *
    *                                               *
    * * * * * * * * * * * * * * * * * * * * * * * * * **/

namespace interne
{
    namespace graphic
    {
        #if defined SDL_SUPPORT
            CGUIVideo::CGUIVideo(SVideo *d, bool run, bool loop) : data->Play(run), data->Replay(loop), lastTime(0), data(d), time(0), frame(0), io(0)
            {
                bmp = SDL_CreateYUVOverlay(data->width, data->height, SDL_YV12_OVERLAY, screen);
                data->Play = run;
                data->Replay = loop;
            }
        #elif defined IRRLICHT_SUPPORT
            CGUIVideo::CGUIVideo(irr::video::IVideoDriver*drive,irr::ITimer *time, SVideo *d, bool run, bool loop) :
                driver(drive),  Timer(time), lastTime(0), data(d), time(0), frame(0), io(0)
            {
                VTexture = driver->addTexture(irr::core::dimension2d<irr::u32>(data->width,data->height), "CGUIVideo::VTexture", irr::video::ECF_R8G8B8);
                if(!VTexture) throw "irr::video::IVideoDriver::addTexture fail in CGUIVideo";
            }
        #endif
        CGUIVideo::~CGUIVideo()
        {
            #ifdef IRRLICHT_SUPPORT
                driver->removeTexture(VTexture);
            #endif
        }
        /********** video VIEW *********/
        void CGUIVideo::setFPS(double fps)
        {
            data->videoFPS = fps;
        }
        void CGUIVideo::WindowFPS()
        {
            #if defined SDL_SUPPORT
                ++i;
                if(SDL_GetTicks() - time > 1000)
                {
                    windowFPS = i - frame;
                    time = SDL_GetTicks();
                    frame = i;
                }
            #elif defined IRRLICHT_SUPPORT
                data->windowFPS = driver->getFPS();
            #elif SFML_SUPPORT
                ++i;
                if(timer.GetElapsedTime() - time)
                {
                    windowFPS = i - frame;
                    time = timer.GetElapsedTime();
                    frame = i;
                }
            #endif
        }
        bool CGUIVideo::refreshByTime()
        {
            if(data->Play
                    #if defined   SDL_SUPPORT
                        && SDL_GetTicks() - lastTime > videoFPS*1000
                    #elif defined SFML_SUPPORT
                        && timer.GetElapsedTime() > videoFPS
                    #elif defined IRRLICHT_SUPPORT
                        && Timer->getRealTime() - lastTime > data->videoFPS*1000
                    #endif
              )
            {
                #if defined SDL_SUPPORT
                    lastTime = SDL_GetTicks();
                #elif defined SFML_SUPPORT
                    timer.Reset();
                #elif defined IRRLICHT_SUPPORT
                    lastTime = Timer->getRealTime();
                #endif
                return refresh();
            }

            return true;
        }
        bool CGUIVideo::refreshByFPS()
        {
            WindowFPS();
            int i = (int)(data->getTotalFrame() / data->videoFPS);
            io = io+i;
            data->goToFrame((int)io);
        }
        bool CGUIVideo::refresh()
        {
            return data->makeFrame();
        }
        /** ******************************************************* **/
        #if defined SDL_SUPPORT
        bool CGUIVideo::draw(SDL_Surface *screen, SDL_Rect rect)
        {
            WindowFPS();
            if(Play && frame)
            {
                SDL_LockYUVOverlay(bmp);
                pict.data[0] = bmp->pixels[0];
                pict.data[1] = bmp->pixels[2];
                pict.data[2] = bmp->pixels[1];

                pict.linesize[0] = bmp->pitches[0];
                pict.linesize[1] = bmp->pitches[2];
                pict.linesize[2] = bmp->pitches[1];

                img_convert(&pict, PIX_FMT_YUVJ420P,(AVPicture *)Frame,videoCodecCtx->pix_fmt,width,height);
                SDL_UnlockYUVOverlay(bmp);
                SDL_DisplayYUVOverlay(bmp, &rect);
            }
        }
        #elif defined IRRLICHT_SUPPORT
        SVideo* CGUIVideo::getVideoData()
        {
            return data;
        }
        irr::video::ITexture* CGUIVideo::getTexture()
        {
            return VTexture;
        }
        irr::video::ITexture* CGUIVideo::draw()
        {
            WindowFPS();//temporary, wait to dev synchronization video
            if(data->Play && data->frame && data->drawFrame)
            {
                irr::u32 *tBits = (irr::u32*)VTexture->lock();
                for(irr::u32 x=0; x<data->width; ++x)
                {
                    for(irr::u32 y=0; y<data->height; ++y)
                    {
                        int p = x*3+y*data->FrameRGB->linesize[0];
                        tBits[y*data->width+x] = data->FrameRGB->data[0][p]   << 16 |
                                                 data->FrameRGB->data[0][p+1] << 8 |
                                                 data->FrameRGB->data[0][p+2];
                    }
                }
                VTexture->unlock();

                data->drawFrame = false;
            }
            return VTexture;
        }
        #endif
    }
}
