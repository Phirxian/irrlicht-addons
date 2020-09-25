#include "CGUITextSlider.h"
#include <irrlicht/IGUIEnvironment.h>
#include <iostream>

namespace irr
{
    namespace gui
    {
        CGUITextSlider::CGUITextSlider(IGUIEnvironment *environment, IGUIElement *parent, const core::recti &size, s32 id) noexcept
            : IGUIComboBox(environment, parent, id, size), selected(0), buttonSize(25), mode(ETSM_HORIZONTAL)
        {
            prev = environment->addButton({0, 0, 0, 0}, this, -1, L"");
            next = environment->addButton({0, 0, 0, 0}, this, -1, L"");
            text = environment->addStaticText(L"", {0, 0, 0, 0}, true, true, this);
            setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
            setRelativePosition(size);
        }
        CGUITextSlider::~CGUITextSlider() noexcept
        {
        }
        bool CGUITextSlider::OnEvent(const irr::SEvent &ev)
        {
            s32 oldSelection = selected;

            if(ev.EventType == irr::EET_GUI_EVENT &&
               ev.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED)
            {
                if(ev.GUIEvent.Caller == prev)
                    setSelected((selected-1)%Items.size());
                if(ev.GUIEvent.Caller == next)
                    setSelected((selected+1)%Items.size());
            }

            if(ev.EventType == irr::EET_MOUSE_INPUT_EVENT &&
               ev.MouseInput.Event == EMIE_MOUSE_WHEEL)
                setSelected((selected+(int)ev.MouseInput.Wheel)%Items.size());

            if(selected != oldSelection)
            {
                if(Parent)
                {
                    SEvent event;
                    event.EventType = EET_GUI_EVENT;
                    event.GUIEvent.Caller = this;
                    event.GUIEvent.Element = 0;
                    event.GUIEvent.EventType = EGET_COMBO_BOX_CHANGED;
                    Parent->OnEvent(event);
                }
                return true;
            }

            return false;
        }
        void CGUITextSlider::setRelativePosition(const core::rect<s32> &size)
        {
            auto scale = size.getSize();
            IGUIElement::setRelativePosition(size);
            if(mode == ETSM_HORIZONTAL)
            {
                prev->setRelativePosition(core::rect<s32>(
                    0, 0, buttonSize,
                    scale.Height
                ));
                text->setRelativePosition(core::rect<s32>(
                    buttonSize, 0,
                    scale.Width-buttonSize,
                    scale.Height
                ));
                next->setRelativePosition(core::rect<s32>(
                    scale.Width-buttonSize, 0,
                    scale.Width, scale.Height
                ));
            }
            else
            {
                prev->setRelativePosition(core::rect<s32>(
                    0, 0,
                    size.getSize().Width,
                    buttonSize
                ));
                text->setRelativePosition(core::rect<s32>(
                    0, buttonSize, scale.Width,
                    scale.Height-buttonSize
                ));
                next->setRelativePosition(core::rect<s32>(
                    0, scale.Height-buttonSize,
                    scale.Width, scale.Height
                ));
            }
        }
        void CGUITextSlider::setTextAlignment(EGUI_ALIGNMENT horizontal, EGUI_ALIGNMENT vertical)
        {
            text->setTextAlignment(horizontal, vertical);
        }
        /*****************************************/
        u32 CGUITextSlider::addItem(const wchar_t *text, u32 data)
        {
            Items.push_back({text, data});
            return Items.size()-1;
        }
        void CGUITextSlider::clear()
        {
            Items.clear();
            text->setText(L"");
        }
        void CGUITextSlider::removeItem(u32 idx)
        {
            Items.erase(idx);
        }
        /*****************************************/
        s32 CGUITextSlider::getIndexForItemData(u32 data) const
        {
            for(int i = 0; i<Items.size(); ++i)
                if(Items[i].Data == data)
                    return i;
            return -1;
        }
        const wchar_t* CGUITextSlider::getItem(u32 idx) const
        {
            if(Items.size())
                return Items[idx].Name.c_str();
            return nullptr;
        }
        u32 CGUITextSlider::getItemCount() const
        {
            return Items.size();
        }
        u32 CGUITextSlider::getItemData(u32 idx) const
        {
            if(Items.size())
                return Items[idx].Data;
            return 0;
        }
        u32 CGUITextSlider::getMaxSelectionRows() const
        {
            return 1;
        }
        s32 CGUITextSlider::getSelected() const
        {
            return selected;
        }
        void CGUITextSlider::setMaxSelectionRows(u32 max)
        {
            ;
        }
        void CGUITextSlider::setSelected(s32 idx)
        {
            if(Items.size())
                text->setText(Items[idx].Name.c_str());
            selected = idx;
        }
        /*****************************************/
        IGUIStaticText* CGUITextSlider::getStaticText()
        {
            return text;
        }
        IGUIButton* CGUITextSlider::getPrevButton()
        {
            return prev;
        }
        IGUIButton* CGUITextSlider::getNextButton()
        {
            return next;
        }
        /*****************************************/
        void CGUITextSlider::setButtonSize(u32 i)
        {
            buttonSize = i;
            setRelativePosition(getRelativePosition());
        }
        void CGUITextSlider::setMode(E_TEXT_SLIDER_MODE m)
        {
            mode = m;
            setRelativePosition(getRelativePosition());
        }
        E_TEXT_SLIDER_MODE CGUITextSlider::getMode()
        {
            return mode;
        }
        u32 CGUITextSlider::getButtonSize()
        {
            return buttonSize;
        }
    }
}
