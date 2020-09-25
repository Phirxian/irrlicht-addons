#include "IGUIInputOutputContext.h"

#include <irrlicht/ITexture.h>
#include <irrlicht/IrrlichtDevice.h>
#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IVideoDriver.h>

namespace irr
{
    namespace gui
    {
        IGUIOutput::IGUIOutput(IGUIInputOutputContext *env,core::recti rectangle, s32 id, IGUIElement *parent)
            : IGUIElement(EGUIET_ELEMENT, env->guienv, parent, id, rectangle), user(0), context(env), selected(false),
              color{255, 255,255,255}, texture(0), hovored(false)
        {
            #ifdef _DEBUG
                setDebugName("IGUIOutput");
            #endif
        }
        IGUIOutput::~IGUIOutput()
        {
            context->removeOutput(this);
        }
        void IGUIOutput::setTexture(video::ITexture *i)
        {
            texture = i;
            if(texture)
                ImageRect = {{0,0}, texture->getOriginalSize()};
        }
        video::ITexture* IGUIOutput::getTexture()
        {
            return texture;
        }
        void IGUIOutput::setUserData(void *data)
        {
            user = data;
        }
        bool IGUIOutput::isHovored()
        {
            return hovored;
        }
        bool IGUIOutput::isOnSelection()
        {
            return selected;
        }
        void* IGUIOutput::getUserData()
        {
            return user;
        }
        bool IGUIOutput::OnEvent(const SEvent &event)
        {
            if(event.EventType == EET_MOUSE_INPUT_EVENT)
            {
                switch(event.MouseInput.Event)
                {
                    case EMIE_LMOUSE_PRESSED_DOWN:
                        cursor.X = event.MouseInput.X;
                        cursor.Y = event.MouseInput.Y;
                        selected = isPointInside(cursor);
                        return selected;
                    break;
                    case EMIE_LMOUSE_LEFT_UP:
                        cursor.X = event.MouseInput.X;
                        cursor.Y = event.MouseInput.Y;
                        for(unsigned int i = 0; i<context->input.size(); ++i)
                            if(context->input[i]->isHovored())
                                context->input[i]->setLink(this);
                        selected = false;
                        return true;
                    break;
                }

            }
            return IGUIElement::OnEvent(event);
        }
        void IGUIOutput::draw()
        {
            if(isVisible())
            {
                if(texture)
                {
                    core::vector2di size{(s32)texture->getSize().Width,
                                              (s32)texture->getSize().Height};
                    core::recti renderPos;
                        renderPos.UpperLeftCorner  = AbsoluteRect.getCenter()-size/2;
                        renderPos.LowerRightCorner = AbsoluteRect.getCenter()+size/2;
                    Environment->getVideoDriver()->draw2DImage(texture, renderPos, ImageRect, &renderPos, 0, true);
                }
                else Environment->getSkin()->drawIcon(this, EGDI_CURSOR_RIGHT, RelativeRect.getCenter());

                if(selected)
                {
                    cursor = context->device->getCursorControl()->getPosition();
                    Environment->setFocus(this);
                    if(texture)
                    {
                        core::vector2di size{(s32)texture->getSize().Width,
                                                  (s32)texture->getSize().Height};
                        core::recti renderPos;
                            renderPos.UpperLeftCorner  = cursor-size/2;
                            renderPos.LowerRightCorner = cursor+size/2;
                        Environment->getVideoDriver()->draw2DImage(texture, renderPos, ImageRect, &renderPos, 0, true);
                    }
                    else  Environment->getSkin()->drawIcon(this, EGDI_FILE, cursor);
                    context->drawSpline(AbsoluteRect.getCenter(), cursor, color);
                }
            }
            IGUIElement::draw();
        }
    }
}
