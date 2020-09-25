#ifndef __C_GUI_ROUND_PROGRESS_HEADER__
#define __C_GUI_ROUND_PROGRESS_HEADER__

#include <irrlicht/IGUIStaticText.h>
#include <irrlicht/IGUIButton.h>
#include <irrlicht/IGUIComboBox.h>

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
        enum E_TEXT_SLIDER_MODE
        {
            ETSM_HORIZONTAL,
            ETSM_VERTICAL,
            ETSM_COUNT
        };
        class CGUITextSlider : public IGUIComboBox
        {
            private:
                struct SComboData
                {
                    SComboData(const wchar_t *text, u32 data)
                        : Name (text), Data ( data ) {}
                    core::stringw Name;
                    u32 Data;
                };
            public:
                CGUITextSlider(IGUIEnvironment *environment, IGUIElement *parent, const core::recti &size, s32 id = 0) noexcept;
                ~CGUITextSlider() noexcept;

                virtual bool OnEvent(const irr::SEvent&);

                virtual void setRelativePosition(const core::rect<s32>&);
                virtual void setTextAlignment(EGUI_ALIGNMENT horizontal, EGUI_ALIGNMENT vertical);

                virtual u32 addItem(const wchar_t *text, u32 data=0);
                virtual void clear();

                virtual s32 getIndexForItemData(u32 data) const;
                virtual const wchar_t* getItem(u32 idx) const;
                virtual u32 getItemCount() const;
                virtual u32 getItemData(u32 idx) const;
                virtual u32 getMaxSelectionRows() const;
                virtual s32 getSelected() const;
                virtual void removeItem(u32 idx);
                virtual void setMaxSelectionRows(u32 max);
                virtual void setSelected(s32 idx);

                virtual IGUIStaticText* getStaticText();
                virtual IGUIButton* getPrevButton();
                virtual IGUIButton* getNextButton();

                virtual void setButtonSize(u32);
                virtual void setMode(E_TEXT_SLIDER_MODE);
                virtual E_TEXT_SLIDER_MODE getMode();
                virtual u32 getButtonSize();
            protected:
                IGUIButton *prev, *next;
                IGUIStaticText *text;
            private:
                E_TEXT_SLIDER_MODE mode;
                core::array<SComboData> Items;
                s32 selected;
                u32 buttonSize;
        };
    }
}

#endif
