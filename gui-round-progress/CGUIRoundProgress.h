#ifndef __C_GUI_ROUND_PROGRESS_HEADER__
#define __C_GUI_ROUND_PROGRESS_HEADER__

#include <irrlicht/IGUIElement.h>
#include <irrlicht/ITexture.h>
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/SMaterial.h>
#include <irrlicht/S3DVertex.h>

/**
 * Copyright (C) <2014> <Jehan-antoine vayssade>
 * Ovan/Magun contact on irrlicht-fr.org or ovan@sleek-think.ovh
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
**/

namespace irr
{
    namespace gui
    {
        class CGUIRoundProgress : public IGUIElement
        {
            public:
                CGUIRoundProgress(IGUIEnvironment *environment, IGUIElement *parent, const core::recti &size, s32 id = 0) noexcept;
                ~CGUIRoundProgress() noexcept;

                virtual void setProgress(float);
                virtual void setForegroundTexture(video::ITexture*);
                virtual void setBackgroundTexture(video::ITexture*);
                virtual void setColor(const irr::video::SColor&);
                virtual void setRotation(float);

                virtual float getRotation();
                virtual video::SColor getColor();
                virtual video::ITexture* getForegroundTexture();
                virtual video::ITexture* getBackgroundTexture();
                virtual float getProgress();

                virtual void draw();
            protected:
                video::SColor clr;
                video::ITexture *bg, *fg;
                float progress;
                float rotation;
            private:
                irr::u16 idx[16];
                irr::video::SMaterial mat;
                irr::video::IVideoDriver *driver;
        };
    }
}

#endif
