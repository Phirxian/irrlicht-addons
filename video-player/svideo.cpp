#include "svideo.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *           created by Ovan or Magun            *
 *   compile with : lavformat, lavcodec, lavutil *
 *        and other library defined last         *
 *                                               *
 *                 conctact me :                 *
 *                www.irrlicht.fr                *
 *            www.immortal-galaxy.com            *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>

#if defined WIN32 || defined WIN64 || defined _WIN32_ || defined _WIN64_
extern "C"
{
    #include <ffmpeg/avcodec.h>
    #include <ffmpeg/avformat.h>
    #include <ffmpeg/swscale.h>
}
#else
extern "C"
{
//    #include <libavdevice/avdevice.h>
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
    #include <libswscale/swscale.h>
}
#endif

#if LIBAVCODEC_VERSION_MAJOR > 51
int img_convert(AVPicture *dst, PixelFormat dst_pix_fmt, AVPicture *src, PixelFormat pix_fmt, int width, int height)
{
    int av_log = av_log_get_level();
    av_log_set_level(AV_LOG_QUIET);
    SwsContext *img_convert_ctx = sws_getContext(width, height, pix_fmt, width, height, dst_pix_fmt, SWS_BICUBIC, 0, 0, 0);
    int result = sws_scale(img_convert_ctx, src->data, src->linesize, 0, height, dst->data, dst->linesize);
    sws_freeContext(img_convert_ctx);
    av_log_set_level(av_log);
    return result;
}
#endif

#if LIBAVCODEC_VERSION_MAJOR > 55
    int open_input_file(AVFormatContext **fmt_ctx_ptr, const char *filename)
    {
        int err, i;
        AVFormatContext *fmt_ctx;

        fmt_ctx = avformat_alloc_context();

        if ((err = av_open_input_file(&fmt_ctx, filename, (*fmt_ctx_ptr)->iformat, 0, NULL)) < 0) {
            return err;
        }

        if ((err = av_find_stream_info(fmt_ctx)) < 0) {
            return err;
        }

        av_dump_format(fmt_ctx, 0, filename, 0);

        /* bind a decoder to each input stream */
        for (i = 0; i < fmt_ctx->nb_streams; i++) {
            AVStream *stream = fmt_ctx->streams[i];
            AVCodec *codec;

            if (!(codec = avcodec_find_decoder(stream->codec->codec_id))) {
                fprintf(stderr, "Unsupported codec (id=%d) for input stream %d\n",
                        stream->codec->codec_id, stream->index);
            } else if (avcodec_open(stream->codec, codec) < 0) {
                fprintf(stderr, "Error while opening codec for input stream %d\n",
                        stream->index);
            }
        }

        *fmt_ctx_ptr = fmt_ctx;
        return 0;
    }
    #define av_close_input_file(FormatCtx) avformat_close_input(&FormatCtx)
#else
    #define open_input_file(fmt_ctx_ptr, filename) avformat_open_input(fmt_ctx_ptr, filename, NULL, 0)
    #define dump_format(fmt_ctx_ptr, a, filename, b) av_dump_format(fmt_ctx_ptr, 0, filename, 0)
    #define avcodec_open(avctx, codec) avcodec_open2(avctx, codec, 0)
#endif

namespace interne
{

    SVideo::SVideo() : FormatCtx(0), Frame(0), FrameRGB(0), buffer(0), Open(false),
        videoCodecCtx(0), audioCodecCtx(0), dataCodecCtx(0), videoCodec(0), audioCodec(0), dataCodec(0)
    {
        avcodec_register_all();
        av_register_all();
    }
    SVideo::SVideo(const std::string & file, bool sound) : FormatCtx(0), Frame(0), FrameRGB(0), buffer(0),
        videoCodecCtx(0), audioCodecCtx(0), dataCodecCtx(0), videoCodec(0), audioCodec(0), dataCodec(0)
    {
        avcodec_register_all();
        av_register_all();
        open(file, sound);
    }
    SVideo::~SVideo()
    {
        if(buffer)          av_free(buffer);
        if(FrameRGB)        av_free(FrameRGB);
        if(Frame)           av_free(Frame);
        if(videoCodecCtx)   avcodec_close(videoCodecCtx);
        if(FormatCtx)       avformat_close_input(&FormatCtx);
    }
    bool SVideo::open(const std::string &f, bool sound)
    {
        Open = false;
        file = f;
        Sound = sound;

        if(open_input_file(&FormatCtx, file.c_str()))
        {
            Play = Open;
            return Open;
        }

        if(avformat_find_stream_info(FormatCtx, 0) < 0)
        {
            Play = Open;
            return Open;
        }

        dump_format(FormatCtx, 0, file.c_str(), 0);

        videoStream = -1;
        audioStream = -1;
        dataStream = -1;

        for(nFrm = 0; nFrm<FormatCtx->nb_streams; nFrm++)
        {
            switch(FormatCtx->streams[nFrm]->codec->codec_type)
            {
                case AVMEDIA_TYPE_DATA:
                    dataStream = nFrm;
                    dataCodecCtx = FormatCtx->streams[dataStream]->codec;
                break;
                case AVMEDIA_TYPE_AUDIO:
                    audioStream = nFrm;
                    audioCodecCtx = FormatCtx->streams[audioStream]->codec;
                    audioCodec = avcodec_find_decoder(audioCodecCtx->codec_id);
                    avcodec_open(audioCodecCtx, audioCodec);

                    #ifdef SDL_AUDIO_SUPPORT
                        wanted_spec.freq = audioCodecCtx->sample_rate;
                        wanted_spec.channels = audioCodecCtx->channels;
                        wanted_spec.samples = AUDIO_BUFFER_SIZE;
                        wanted_spec.format = AUDIO_S16SYS;
                        wanted_spec.silence = 0;

                        if(SDL_OpenAudio(&wanted_spec, &spec) < 0) {
                            throw "can't open audio device";
                        }
                    #endif
                break;
                case AVMEDIA_TYPE_VIDEO:
                    videoStream = nFrm;
                    videoCodecCtx = FormatCtx->streams[videoStream]->codec;
                    videoCodec = avcodec_find_decoder(videoCodecCtx->codec_id);
                    avcodec_open(videoCodecCtx, videoCodec);
                    videoFPS = (double)FormatCtx->streams[videoStream]->r_frame_rate.den / FormatCtx->streams[videoStream]->r_frame_rate.num;
                    Frame = avcodec_alloc_frame();
                    FrameRGB = avcodec_alloc_frame();
                break;
            }
        }

        #if defined IRRLICHT_SUPPORT
            numBytes = avpicture_get_size(PIX_FMT_RGB24, videoCodecCtx->width, videoCodecCtx->height);
            buffer = (uint8_t*)av_malloc(numBytes*sizeof(uint8_t));
            avpicture_fill((AVPicture*)FrameRGB, buffer, PIX_FMT_RGB24, videoCodecCtx->width, videoCodecCtx->height);
        #else
            numBytes = avpicture_get_size(PIX_FMT_RGB32, videoCodecCtx->width, videoCodecCtx->height);
            buffer = (uint8_t*)av_malloc(numBytes*sizeof(uint8_t));
            avpicture_fill((AVPicture*)FrameRGB, buffer, PIX_FMT_RGB32, videoCodecCtx->width, videoCodecCtx->height);
        #endif

        nFrm = 0;
        width = videoCodecCtx->width;
        height = videoCodecCtx->height;

        Open = true;
        return Open;
    }
    int SVideo::getWidth()
    {
        return width;
    }
    int SVideo::getHeight()
    {
        return height;
    }
    bool SVideo::makeFrame()
    {
        drawFrame = Play || Replay;
        if(!drawFrame) return drawFrame;

        AVPacket packet;
        av_init_packet(&packet);

        if(av_read_frame(FormatCtx, &packet) >= 0)
        {
            if(packet.stream_index == videoStream)
            {
                avcodec_decode_video2(videoCodecCtx, Frame, &frame, &packet);
                if(frame)
                {
                    nFrm++;
                    #ifdef IRRLICHT_SUPPORT
                        img_convert((AVPicture*)FrameRGB, PIX_FMT_RGB24, (AVPicture*)Frame, videoCodecCtx->pix_fmt, width, height);
                    #endif
                }
            }
            else if(packet.stream_index == audioStream)
            {
                avcodec_decode_audio4(audioCodecCtx, Frame, &frame, &packet);
                if(frame)
                {
                    #ifdef SDL_AUDIO_SUPPORT
                        // Mix_Music *audio = Mix_LoadMUS_RW(SDL_RWFromMem(Frame->data[0], Frame->linesize[0]));
                        // ....
                    #endif
                }
            }
            av_free_packet(&packet);
        }
        else
        {
            av_free_packet(&packet);
            if(Replay) return restart() >= 0;
            play(false);
            return false;
        }

        return drawFrame;
    }
    /******************************/
    void SVideo::play(bool b)
    {
        Play = b;
    }
    void SVideo::stop()
    {
        restart();
        Play = false;
    }
    void SVideo::setLoop(bool b)
    {
        Replay = b;
    }
    bool SVideo::isPlay()
    {
        return Play;
    }
    bool SVideo::isLoop()
    {
        return Replay;
    }
    /******************************/
    bool SVideo::goToTime(int sec, int min, int h)
    {
        sec += ((h*60)+min)*60;
        return goToFrame((int)(sec/videoFPS));
    }
    bool SVideo::goToFrame(int frm)
    {
        nFrm = frm;
        return av_seek_frame(FormatCtx, videoStream, frm, AVSEEK_FLAG_BACKWARD) >= 0;
    }
    bool SVideo::restart()
    {
        return goToFrame(0);
    }
    /********** FILE INFO *********/
    int SVideo::getVideoFPS()
    {
        return (int)videoFPS;
    }
    double SVideo::getOriginalFPS()
    {
        return (double)FormatCtx->streams[videoStream]->r_frame_rate.den / FormatCtx->streams[videoStream]->r_frame_rate.num;
    }
    int SVideo::getFrame()
    {
        return nFrm;
    }
    int SVideo::getTime()
    {
        return (int)(nFrm/videoFPS)/60;
    }
    int SVideo::getTotalFrame()
    {
        return FormatCtx->streams[videoStream]->nb_frames;
    }
    int SVideo::getTotalTime()
    {
        return (int)(FormatCtx->streams[videoStream]->nb_frames/videoFPS);
    }
    int SVideo::getWindowFPS()
    {
        return windowFPS;
    }
    /******************************/
}
