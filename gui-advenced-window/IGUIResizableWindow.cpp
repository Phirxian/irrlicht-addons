#include "IGUIResizableWindow.h"

#include <irrlicht/IGUIButton.h>
#include <irrlicht/IGUISkin.h>
#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IGUIFont.h>

namespace irr
{
    namespace gui
    {
        IGUIResizableWindow::IGUIResizableWindow(IGUIEnvironment* environment, core::recti rectangle, IGUIElement *parent)
            : IGUIWindow(environment, parent, -1, rectangle), Dragging(false), IsDraggable(true), Resizing(false), DrawBackground(true), DrawTitlebar(true)
        {
            #ifdef _DEBUG
            setDebugName("IGUIResizableWindow");
            #endif

            // return if we have no skin.
            IGUISkin *skin = environment->getSkin();
            if(!skin) return;

            CurrentIconColor = {255,255,255,255};

            s32 buttonw = skin ? skin->getSize(EGDS_WINDOW_BUTTON_WIDTH) : 15;

            setRelativePosition({50,50,250,500});
            setMinSize({200,200});

            ResizeButton = environment->addButton({199-buttonw,449-buttonw,199,449}, this);
            ResizeButton->setSpriteBank(skin->getSpriteBank());
            ResizeButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_RESIZE), skin->getColor(EGDC_WINDOW_SYMBOL));
            ResizeButton->setDrawBorder(false);
            ResizeButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_RESIZE), skin->getColor(EGDC_WINDOW_SYMBOL));
            ResizeButton->setEnabled(false);
            ResizeButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT);
            ResizeButton->setSubElement(true);

            s32 posx = RelativeRect.getWidth() - buttonw - 4;

            CloseButton = environment->addButton({posx, 3, posx + buttonw, 3 + buttonw}, this, -1,
                          L"", skin ? skin->getDefaultText(EGDT_WINDOW_CLOSE) : L"Close" );
            CloseButton->setSubElement(true);
            CloseButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
            CloseButton->setTabStop(false);
            posx -= buttonw + 2;

            RestoreButton = environment->addButton({posx, 3, posx + buttonw, 3 + buttonw}, this, -1,
                            L"", skin ? skin->getDefaultText(EGDT_WINDOW_RESTORE) : L"Restore" );
            RestoreButton->setVisible(false);
            RestoreButton->setSubElement(true);
            RestoreButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
            RestoreButton->setTabStop(false);
            posx -= buttonw + 2;

            MinButton = environment->addButton({posx, 3, posx + buttonw, 3 + buttonw}, this, -1,
                        L"", skin ? skin->getDefaultText(EGDT_WINDOW_MINIMIZE) : L"Minimize" );
            MinButton->setSubElement(true);
            MinButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
            MinButton->setVisible(false);
            MinButton->setTabStop(false);

            MinButton->grab();
            RestoreButton->grab();
            CloseButton->grab();
            ResizeButton->grab();

            // this element is a tab group
            setTabGroup(true);
            setTabStop(true);
            setTabOrder(-1);

            refreshSprites();
            updateClientRect();
        }
        IGUIResizableWindow::~IGUIResizableWindow()
        {
            if(ResizeButton)  ResizeButton->drop();
            if(MinButton)     MinButton->drop();
            if(RestoreButton) RestoreButton->drop();
            if(CloseButton)   CloseButton->drop();
        }
        void IGUIResizableWindow::refreshSprites()
        {
            if(!Environment) return;
            IGUISkin* skin  = Environment->getSkin();
            if(!skin) return;

            IGUISpriteBank* sprites = skin->getSpriteBank();
            if(!sprites) return;

            CurrentIconColor = skin->getColor(isEnabled() ? EGDC_WINDOW_SYMBOL : EGDC_GRAY_WINDOW_SYMBOL);

            if(sprites)
            {
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
        }
        void IGUIResizableWindow::draw()
        {
            if(IsVisible)
            {
                IGUISkin* skin = Environment->getSkin();
                updateClientRect();

                if(CurrentIconColor != skin->getColor(isEnabled() ? EGDC_WINDOW_SYMBOL : EGDC_GRAY_WINDOW_SYMBOL) )
                    refreshSprites();

                core::recti rect = AbsoluteRect;

                // draw body fast
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
                        if(font)
                        {
                            font->draw(Text.c_str(), rect,
                                    skin->getColor(IsActive ? EGDC_ACTIVE_CAPTION : EGDC_INACTIVE_CAPTION),
                                    false, true, &AbsoluteClippingRect);
                        }
                    }
                }
            }
            IGUIElement::draw();
        }
        bool IGUIResizableWindow::OnEvent(const SEvent &event)
        {
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
                        if(Parent && ((event.GUIEvent.Caller == this) ||
                                       isMyChild(event.GUIEvent.Caller) ||
                                       event.GUIEvent.Caller == ResizeButton))
                        {
                            Parent->bringToFront(this);
                            IsActive = true;
                        }
                        else
                        {
                            IsActive = false;
                        }
                    }
                    else if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
                    {
                        if(event.GUIEvent.Caller == CloseButton)
                        {
                            if(Parent)
                            {
                                SEvent e;
                                e.EventType = EET_GUI_EVENT;
                                e.GUIEvent.Caller = this;
                                e.GUIEvent.Element = 0;
                                e.GUIEvent.EventType = EGET_ELEMENT_CLOSED;

                                if(!Parent->OnEvent(e)) remove();
                            }
                            else remove();

                            return true;
                        }
                    }
                break;
                case EET_MOUSE_INPUT_EVENT:
                    switch(event.MouseInput.Event)
                    {
                        case EMIE_LMOUSE_PRESSED_DOWN:
                        {
                            DragStart.X = event.MouseInput.X;
                            DragStart.Y = event.MouseInput.Y;

                            IGUIElement* clickedElement = getElementFromPoint(DragStart);

                            if(clickedElement == ResizeButton)
                            {
                                IsActive = true;
                                Resizing = true;
                                if(Parent) Parent->bringToFront(this);
                                return true;
                            }
                            else if(clickedElement == this || isMyChild(event.GUIEvent.Caller))
                            {
                                IsActive = true;
                                Dragging = IsDraggable;
                                if(Parent) Parent->bringToFront(this);
                                return true;
                            }
                            else
                            {
                                IsActive = false;
                            }
                        }
                        break;
                        case EMIE_LMOUSE_LEFT_UP:
                            if(Dragging || Resizing)
                            {
                                Dragging = false;
                                Resizing = false;
                                return true;
                            }
                        break;
                        case EMIE_MOUSE_MOVED:
                            if(Dragging || Resizing)
                            {
                                // gui window should not be dragged outside of its parent
                                if(Parent &&(event.MouseInput.X < Parent->getAbsolutePosition().UpperLeftCorner.X +1 ||
                                              event.MouseInput.Y < Parent->getAbsolutePosition().UpperLeftCorner.Y +1 ||
                                              event.MouseInput.X > Parent->getAbsolutePosition().LowerRightCorner.X -1 ||
                                              event.MouseInput.Y > Parent->getAbsolutePosition().LowerRightCorner.Y -1))
                                {
                                    return true;
                                }
                                core::position2di diff(event.MouseInput.X - DragStart.X, event.MouseInput.Y - DragStart.Y);
                                if(Dragging)
                                {
                                    move(diff);
                                    DragStart.X = event.MouseInput.X;
                                    DragStart.Y = event.MouseInput.Y;
                                }
                                else if(Resizing)
                                {
                                    core::position2di dp = RelativeRect.LowerRightCorner + diff;
                                    setRelativePosition(core::recti(RelativeRect.UpperLeftCorner, dp));
                                    DragStart += dp - RelativeRect.LowerRightCorner + diff;
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
            return Parent ? Parent->OnEvent(event) : false;
        }
        IGUIButton* IGUIResizableWindow::getResizeButton() const
        {
            return ResizeButton;
        }
        IGUIButton* IGUIResizableWindow::getCloseButton() const
        {
            return CloseButton;
        }
        IGUIButton* IGUIResizableWindow::getMinimizeButton() const
        {
            return MinButton;
        }
        IGUIButton* IGUIResizableWindow::getMaximizeButton() const
        {
            return RestoreButton;
        }
        bool IGUIResizableWindow::isDraggable() const
        {
            return IsDraggable;
        }
        void IGUIResizableWindow::setDraggable(bool draggable)
        {
            IsDraggable = draggable;

            if(Dragging && !IsDraggable)
                Dragging = false;
        }
        void IGUIResizableWindow::setDrawBackground(bool draw)
        {
            DrawBackground = draw;
        }
        bool IGUIResizableWindow::getDrawBackground() const
        {
            return DrawBackground;
        }
        void IGUIResizableWindow::setDrawTitlebar(bool draw)
        {
            DrawTitlebar = draw;
        }
        bool IGUIResizableWindow::getDrawTitlebar() const
        {
            return DrawTitlebar;
        }
        void IGUIResizableWindow::updateClientRect()
        {
            if(!DrawBackground)
            {
                ClientRect = {0,0, AbsoluteRect.getWidth(), AbsoluteRect.getHeight()};
                return;
            }
            IGUISkin* skin = Environment->getSkin();
            skin->draw3DWindowBackground(this, DrawTitlebar,
                skin->getColor(IsActive ? EGDC_ACTIVE_BORDER : EGDC_INACTIVE_BORDER),
                AbsoluteRect, &AbsoluteClippingRect, &ClientRect);
            ClientRect -= AbsoluteRect.UpperLeftCorner;
        }
        core::recti IGUIResizableWindow::getClientRect() const
        {
            return ClientRect;
        }
        void IGUIResizableWindow::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
        {
            IGUIWindow::serializeAttributes(out,options);

            out->addBool("IsDraggable", IsDraggable);
            out->addBool("DrawBackground", DrawBackground);
            out->addBool("DrawTitlebar", DrawTitlebar);
            out->addBool("IsCloseVisible", CloseButton->isVisible());
            out->addBool("IsMinVisible", MinButton->isVisible());
            out->addBool("IsRestoreVisible", RestoreButton->isVisible());
            out->addBool("IsResizableVisible", ResizeButton->isVisible());
        }
        void IGUIResizableWindow::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
        {
            IGUIWindow::deserializeAttributes(in,options);

            Dragging = false;
            IsActive = false;
            Resizing = false;

            IsDraggable = in->getAttributeAsBool("IsDraggable");
            DrawBackground = in->getAttributeAsBool("DrawBackground");
            DrawTitlebar = in->getAttributeAsBool("DrawTitlebar");

            CloseButton->setVisible(in->getAttributeAsBool("IsCloseVisible"));
            MinButton->setVisible(in->getAttributeAsBool("IsMinVisible"));
            RestoreButton->setVisible(in->getAttributeAsBool("IsRestoreVisible"));
            ResizeButton->setVisible(in->getAttributeAsBool("IsResizableVisible"));

            updateClientRect();
        }
    }
}
