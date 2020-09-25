#include "IGUIDynamicWindows.h"

#include <irrlicht/IrrlichtDevice.h>
#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IGUIButton.h>
#include <irrlicht/IGUISkin.h>
#include <irrlicht/IGUIFont.h>

namespace irr
{
    namespace gui
    {
        IGUIDynamicWindows::IGUIDynamicWindows(IrrlichtDevice *d, core::recti i, u32 id)
            : IGUIWindow(d->getGUIEnvironment(), d->getGUIEnvironment()->getRootGUIElement(), id, i),
              Dragging(false), IsDraggable(true), DrawBackground(true), DrawTitlebar(true), IsActive(false), dev(d), SmoothTime(3000)
        {
            IGUISkin* skin = 0;
            if(Environment) skin = Environment->getSkin();
            CurrentIconColor = video::SColor(255,255,255,255);

            s32 buttonw = 15;
            if(skin) buttonw = skin->getSize(EGDS_WINDOW_BUTTON_WIDTH);
            s32 posx = RelativeRect.getWidth() - buttonw - 4;

            CloseButton = Environment->addButton(core::recti(posx, 3, posx + buttonw, 3 + buttonw), this, -1, L"", skin ? skin->getDefaultText(EGDT_WINDOW_CLOSE) : L"Close" );
            CloseButton->setSubElement(true);
            CloseButton->setTabStop(false);
            CloseButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
            posx -= buttonw + 2;

            RestoreButton = Environment->addButton(core::recti(posx, 3, posx + buttonw, 3 + buttonw), this, -1, L"", skin ? skin->getDefaultText(EGDT_WINDOW_RESTORE) : L"Restore" );
            RestoreButton->setVisible(false);
            RestoreButton->setSubElement(true);
            RestoreButton->setTabStop(false);
            RestoreButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
            posx -= buttonw + 2;

            MinButton = Environment->addButton(core::recti(posx, 3, posx + buttonw, 3 + buttonw), this, -1, L"", skin ? skin->getDefaultText(EGDT_WINDOW_MINIMIZE) : L"Minimize" );
            MinButton->setVisible(false);
            MinButton->setSubElement(true);
            MinButton->setTabStop(false);
            MinButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);

            MinButton->grab();
            RestoreButton->grab();
            CloseButton->grab();

            setTabGroup(true);
            setTabStop(true);
            setTabOrder(-1);

            refreshSprites();
        }
        IGUIDynamicWindows::~IGUIDynamicWindows()
        {
        }
        void IGUIDynamicWindows::move(core::position2di absoluteMovement)
        {
            Drag.end = absoluteMovement;
            Moving = false;
            SEvent e;
                e.EventType = EET_GUI_EVENT;
                e.GUIEvent.Caller = this;
                e.GUIEvent.Element = 0;
                e.GUIEvent.EventType = EGET_COUNT;
            dev->postEventFromUser(e);
            IGUIWindow::move(absoluteMovement);
        }
        bool IGUIDynamicWindows::OnEvent(const SEvent& event)
        {
            if(!isEnabled()) return IGUIElement::OnEvent(event);
            switch(event.EventType)
            {
                case EET_GUI_EVENT:
                    if(event.GUIEvent.EventType == EGET_ELEMENT_FOCUS_LOST)
                    {
                        Dragging = false;
                        IsActive = false;
                    }
                    else if(event.GUIEvent.EventType == EGET_ELEMENT_FOCUSED)
                    {
                        if(Parent && ((event.GUIEvent.Caller == this) || isMyChild(event.GUIEvent.Caller)))
                        {
                            Parent->bringToFront(this);
                            IsActive = true;
                        }
                        else IsActive = false;
                    }
                    else if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
                    {
                        if(event.GUIEvent.Caller == getCloseButton())
                        {
                            if(Parent)
                            {
                                SEvent e;
                                e.EventType = EET_GUI_EVENT;
                                e.GUIEvent.Caller = this;
                                e.GUIEvent.Element = 0;
                                e.GUIEvent.EventType = EGET_ELEMENT_CLOSED;
                                if(!Parent->OnEvent(e)) remove();
                                return true;
                            }
                            else
                            {
                                remove();
                                return true;
                            }
                        }
                    }
                break;
                case EET_MOUSE_INPUT_EVENT:
                    switch(event.MouseInput.Event)
                    {
                        case EMIE_LMOUSE_PRESSED_DOWN:
                            Moving = Dragging = IsDraggable;
                            Drag.start.X = event.MouseInput.X;
                            Drag.start.Y = event.MouseInput.Y;
                            if(Parent) Parent->bringToFront(this);
                            return true;
                        case EMIE_LMOUSE_LEFT_UP:
                            Dragging = false;
                            StartTime = dev->getTimer()->getTime();
                            return true;
                        case EMIE_MOUSE_MOVED:
                            if(!event.MouseInput.isLeftPressed()) Dragging = false;
                            if(Dragging)
                            {
                                if(Parent &&
                                    (event.MouseInput.X < Parent->getAbsolutePosition().UpperLeftCorner.X +1 ||
                                     event.MouseInput.Y < Parent->getAbsolutePosition().UpperLeftCorner.Y +1 ||
                                     event.MouseInput.X > Parent->getAbsolutePosition().LowerRightCorner.X -1 ||
                                     event.MouseInput.Y > Parent->getAbsolutePosition().LowerRightCorner.Y -1)
                                   ) return true;

                                core::position2di newPos;
                                newPos.X = event.MouseInput.X;
                                newPos.Y = event.MouseInput.Y;

                                if(newPos != Drag.end)
                                {
                                    Drag.start = Drag.end;
                                    Drag.end = newPos;
                                }

                                return true;
                            }
                        break;
                        default:
                        break;
                    }
                default:
                break;
            }
            return IGUIElement::OnEvent(event);
        }
        u32 IGUIDynamicWindows::getSmoothTime()
        {
            return SmoothTime;
        }
        IGUIButton* IGUIDynamicWindows::getCloseButton() const
        {
            return CloseButton;
        }
        IGUIButton* IGUIDynamicWindows::getMinimizeButton() const
        {
            return MinButton;
        }
        IGUIButton* IGUIDynamicWindows::getMaximizeButton() const
        {
            return RestoreButton;
        }
        bool IGUIDynamicWindows::isDraggable() const
        {
            return IsDraggable;
        }
        void IGUIDynamicWindows::setDraggable(bool draggable)
        {
            IsDraggable = draggable;

            if(Dragging && !IsDraggable)
                Dragging = false;
        }
        void IGUIDynamicWindows::setSmoothTime(u32 time)
        {
            SmoothTime = time;
        }
        void IGUIDynamicWindows::setDrawBackground(bool draw)
        {
            DrawBackground = draw;
        }
        bool IGUIDynamicWindows::getDrawBackground() const
        {
            return DrawBackground;
        }
        void IGUIDynamicWindows::setDrawTitlebar(bool draw)
        {
            DrawTitlebar = draw;
        }
        bool IGUIDynamicWindows::getDrawTitlebar() const
        {
            return DrawTitlebar;
        }
        core::recti IGUIDynamicWindows::getClientRect() const
        {
            return ClientRect;
        }
        void IGUIDynamicWindows::refreshSprites()
        {
            IGUISkin* skin  = Environment->getSkin();
            IGUISpriteBank* sprites = skin->getSpriteBank();

            CurrentIconColor = skin->getColor(isEnabled() ? EGDC_WINDOW_SYMBOL : EGDC_GRAY_WINDOW_SYMBOL);

            CloseButton->setSpriteBank(sprites);
            CloseButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_CLOSE), CurrentIconColor);
            CloseButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_CLOSE), CurrentIconColor);

            RestoreButton->setSpriteBank(sprites);
            RestoreButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_RESTORE), CurrentIconColor);
            RestoreButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_RESTORE), CurrentIconColor);

            MinButton->setSpriteBank(sprites);
            MinButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_MINIMIZE), CurrentIconColor);
            MinButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_MINIMIZE), CurrentIconColor);
        }
        void IGUIDynamicWindows::updateClientRect()
        {
            if(!DrawBackground)
            {
                ClientRect = core::recti(0,0, AbsoluteRect.getWidth(), AbsoluteRect.getHeight());
                return;
            }
            IGUISkin* skin = Environment->getSkin();
            skin->draw3DWindowBackground(this, DrawTitlebar,
            skin->getColor(IsActive ? EGDC_ACTIVE_BORDER : EGDC_INACTIVE_BORDER), AbsoluteRect, &AbsoluteClippingRect, &ClientRect);
            ClientRect -= AbsoluteRect.UpperLeftCorner;
        }
        void IGUIDynamicWindows::draw()
        {
            if(IsVisible)
            {
                if(Moving)
                {
                    u32 elapsed = dev->getTimer()->getTime()-StartTime;

                    f32 pos = elapsed / SmoothTime;
                    core::position2di newPos;
                        newPos.X = Drag.end.X + Drag.getVector().X;
                        newPos.Y = Drag.end.Y + Drag.getVector().Y;
                    move(newPos);

                    if(elapsed >= SmoothTime && !Dragging)
                    {
                        Moving = false;
                        Drag.end = getAbsolutePosition().UpperLeftCorner;
                    }
                }

                IGUISkin* skin = Environment->getSkin();
                updateClientRect();

                if(CurrentIconColor != skin->getColor(isEnabled() ? EGDC_WINDOW_SYMBOL : EGDC_GRAY_WINDOW_SYMBOL))
                    refreshSprites();

                core::recti rect = AbsoluteRect;
                if(DrawBackground)
                {
                    rect = skin->draw3DWindowBackground(this, DrawTitlebar,
                            skin->getColor(IsActive ? EGDC_ACTIVE_BORDER : EGDC_INACTIVE_BORDER),
                            AbsoluteRect, &AbsoluteClippingRect);

                    if(DrawTitlebar && Text.size())
                    {
                        rect.UpperLeftCorner.X += skin->getSize(EGDS_TITLEBARTEXT_DISTANCE_X);
                        rect.UpperLeftCorner.Y += skin->getSize(EGDS_TITLEBARTEXT_DISTANCE_Y);
                        rect.LowerRightCorner.X -= skin->getSize(EGDS_WINDOW_BUTTON_WIDTH) + 5;

                        IGUIFont* font = skin->getFont(EGDF_WINDOW);
                        if(font) font->draw(Text.c_str(), rect, skin->getColor(IsActive ? EGDC_ACTIVE_CAPTION:EGDC_INACTIVE_CAPTION), false, true, &AbsoluteClippingRect);
                    }
                }
            }
            IGUIElement::draw();
        }
    }
}
