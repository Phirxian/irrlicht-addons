#ifndef _GAME_INTRO_H_
#define _GAME_INTRO_H_

#include <string>

#include "cguivideo.h"
namespace interne
{
    namespace graphic
    {
        class GameIntro
        {
            public:
                GameIntro(irr::IrrlichtDevice*, const std::string & videoFile, bool rsz = false);
                virtual ~GameIntro();
                virtual bool externalEvent(irr::SEvent event);
                bool draw();

                SVideo vi;
                CGUIVideo *intro;
            protected:
                bool resize_for_render;
                irr::IrrlichtDevice *device;
                irr::core::dimension2d<irr::u32> current_render_size;
        };
    }
}
#endif // _GAME_INTRO_H_
