#ifndef __C_GUI_COLOR_PICKER_HEADER__
#define __C_GUI_COLOR_PICKER_HEADER__

#include <irrlicht/IGUIElement.h>
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
        class IGUIButton;
        class IGUIStaticText;
        class IGUIScrollBar;

        class CGUIColorPicker : public IGUIElement
        {
            public:
                CGUIColorPicker(IGUIEnvironment *environment, IGUIElement *parent, s32 id = 0) noexcept;
                ~CGUIColorPicker() noexcept;

                virtual void setRelativePosition(const core::recti &r);

                virtual bool OnEvent(const SEvent&) noexcept;
                virtual void updateAbsolutePosition();

                virtual void setPickedColor(const video::SColor&) noexcept;
                virtual const video::SColor& getPickedColor() const noexcept;

                virtual void setBackgroundColor(const video::SColor&) noexcept;
                virtual const video::SColor& getBackgroundColor() const noexcept;

                virtual void draw();
            protected:
                bool isGradient, isColor, isInside;
                virtual void recalculatePickedColor() noexcept;
                virtual void createAlphaTexture() noexcept;
                virtual void createGradientTexture() noexcept;
            protected:
                IGUIButton      *close;
                IGUIScrollBar   *scroll;
                video::ITexture *img[2];
            protected:
                video::SColor    pickcolor, color;
                video::SColor    background, white, black, alpha;
                core::recti      box, pickbox, gradient;
                core::vector2di  pickpos;
                int              colorpos;
        };
    }
}

#endif
