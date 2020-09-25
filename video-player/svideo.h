#ifndef _SVIDEO_H_
#define _SVIDEO_H_

/** * * * * * * * * * * * * * * * * * * * * * * * * *
    *                                               *
    *           created by Ovan or Magun            *
    *   compile with : lavformat, lavcodec, lavutil   *
    *        and other library defined last         *
    *                                               *
    *                 conctact me :                 *
    *                www.irrlicht.fr                *
    *            www.immortal-galaxy.com            *
    *                                               *
    * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <stdint.h>
#if defined WIN32 || defined WIN64 || defined _WIN32_ || defined _WIN64_
    #define WINDOWS
#endif

//#define SDL_SUPPORT
//#define IRRLICHT_SUPPORT

#define SDL_AUDIO_SUPPORT
#define AUDIO_BUFFER_SIZE 1024

#ifdef SDL_AUDIO_SUPPORT
extern "C"
{
    #include <SDL_audio.h>
    #include <SDL_mixer.h>
}
#endif

struct AVFormatContext;
struct AVCodecContext;
struct AVCodec;
struct AVPicture;
struct AVFrame;

#include <string>

namespace interne
{
    namespace graphic
    {
        class CGUIVideo;
    }
    struct SVideo
    {
        public:
            SVideo();
            SVideo(const std::string & file, bool sound = false);
            ~SVideo();

            bool open(const std::string & file, bool sound);

            void play(bool p = true);
            void stop();
            bool restart();
            bool isPlay();
            bool isOpen();

            void setLoop(bool b = false);
            bool isLoop();

            int     getWindowFPS();
            int     getVideoFPS();
            double  getOriginalFPS();

            int     getFrame();
            int     getTotalFrame();

            int     getTime();
            int     getTotalTime();

            bool    goToTime(int sec = 0, int min = 0, int h = 0);
            bool    goToFrame(int frm);

            char   *getAuthor();
            char   *getAlbum();
            char   *getTitle();
            char   *getCopyright();
            char   *getComment();
            char   *getGenre();

            int     getYear();
            int     getTrack();

            int     getWidth();
            int     getHeight();

            bool makeFrame();
        protected:
            std::string file;

            AVFrame         *Frame, *FrameRGB;
            AVFormatContext *FormatCtx;
            AVCodecContext  *videoCodecCtx , *audioCodecCtx , *dataCodecCtx;
            AVCodec         *videoCodec    , *audioCodec    , *dataCodec;

            uint8_t *buffer;

            double videoFPS;
            int  nFrm, frame, numBytes, windowFPS, width, height;
            int  videoStream, audioStream, dataStream;
            bool drawFrame, Sound, Play, Replay, Open;

            #if defined SDL_AUDIO_SUPPORT
              SDL_AudioSpec wanted_spec, spec;
            #endif
        private:
            friend class graphic::CGUIVideo;
    };
}
#endif
