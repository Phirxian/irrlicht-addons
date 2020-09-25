#include "IGUIInputOutputContext.h"
#include "IGUIOutput.h"
#include "IGUIInput.h"

#include <irrlicht/IVideoDriver.h>
#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/ITexture.h>

namespace irr
{
    namespace gui
    {
        IGUIInput::IGUIInput(IGUIInputOutputContext *env, core::recti rectangle, s32 id, IGUIElement *parent) :
            IGUIElement(EGUIET_ELEMENT, env->guienv, parent, id, rectangle)
        {
            slot = 0;
            hovored = false;
            context = env;
            #ifdef _DEBUG
                setDebugName("IGUIInput");
            #endif
            color = {255, 255,255,255};
            texture = 0;
            link = 0;
        }
        IGUIInput::~IGUIInput()
        {
            context->removeInput(this);
        }
        void IGUIInput::setLink(IGUIOutput *nl)
        {
            link = nl;
            if(nl) setSlotTexture(nl->getTexture());
            else setSlotTexture(texture);
        }
        IGUIOutput *IGUIInput::getLink()
        {
            return link;
        }
        void IGUIInput::setTexture(video::ITexture *i)
        {
            texture = i;
            if(!slot)
                setSlotTexture(texture);
        }
        void IGUIInput::setSlotTexture(video::ITexture *i)
        {
            slot = i;
            if(slot)
                ImageRect = {{0,0}, slot->getOriginalSize()};
            else if(texture)
                ImageRect = {{0,0}, texture->getOriginalSize()};
        }
        video::ITexture* IGUIInput::getSlotTexture()
        {
            return slot;
        }
        video::ITexture* IGUIInput::getTexture()
        {
            return texture;
        }
        bool IGUIInput::isHovored()
        {
            return hovored;
        }
        bool IGUIInput::OnEvent(const SEvent &event)
        {
            if(event.EventType == EET_GUI_EVENT)
            {
                if(event.GUIEvent.EventType == EGET_ELEMENT_HOVERED) hovored = true;
                if(event.GUIEvent.EventType == EGET_ELEMENT_LEFT) hovored = false;
            }
            if(event.EventType == EET_MOUSE_INPUT_EVENT)
            {
                switch(event.MouseInput.Event)
                {
                    case EMIE_MOUSE_MOVED:
                        hovored = isPointInside(core::vector2d<int>(event.MouseInput.X, event.MouseInput.Y));
                    break;
                    case EMIE_LMOUSE_DOUBLE_CLICK:
                        setLink(0);
                        return true;
                    break;
                    default:
                    break;
                }
            }
            return IGUIElement::OnEvent(event);
        }
        void IGUIInput::draw()
        {
            if(isVisible())
            {
                //if(slot) Environment->getVideoDriver()->draw2DImage(slot, AbsoluteRect, ImageRect, &AbsoluteClippingRect,0, true);
                if(texture)
                {
                    core::vector2di size((int)texture->getSize().Width, (int)texture->getSize().Height);
                    core::recti renderPos;
                        renderPos.UpperLeftCorner  = AbsoluteRect.getCenter()-size/2;
                        renderPos.LowerRightCorner = AbsoluteRect.getCenter()+size/2;
                    Environment->getVideoDriver()->draw2DImage(slot, renderPos, ImageRect, &renderPos, 0, true);
                }
                else Environment->getSkin()->drawIcon(this, EGDI_CURSOR_RIGHT, RelativeRect.getCenter());
            }
            if(link)
                context->drawSpline(link->getAbsolutePosition().getCenter(), AbsoluteRect.getCenter(), color);
            IGUIElement::draw();
        }
    }
}
