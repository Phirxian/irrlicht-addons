#include "IGUIInputOutputContext.h"

#include <irrlicht/IrrlichtDevice.h>
#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IVideoDriver.h>

namespace irr
{
    namespace gui
    {
        IGUIInputOutputContext::IGUIInputOutputContext(IrrlichtDevice * dev) : device(dev), guienv(dev->getGUIEnvironment())
        {
        }
        bool IGUIInputOutputContext::OnEvent(const SEvent &event)
        {
            IGUIOutput *out = 0;
            for(unsigned int i = 0; i<output.size(); ++i)
                if(output[i]->isOnSelection()) out = output[i];

            if(event.EventType == EET_MOUSE_INPUT_EVENT)
            {
                switch(event.MouseInput.Event)
                {
                    case EMIE_LMOUSE_LEFT_UP:
                        if(out)
                        {
                            for(unsigned int i = 0; i<input.size(); ++i)
                                if(input[i]->isHovored())
                                    input[i]->setLink(out);
                            out->selected = false;
                        }
                        return true;
                    break;
                }

            }
            return false;
        }
        IGUIInput* IGUIInputOutputContext::addInput(core::recti rect, IGUIElement *parent)
        {
            IGUIInput *in = new IGUIInput(this, rect, -1, parent ? parent : guienv->getRootGUIElement());
                input.push_back(in);
                in->grab();
            return in;
        }
        IGUIOutput* IGUIInputOutputContext::addOutput(core::recti rect, IGUIElement *parent)
        {
            IGUIOutput *out = new IGUIOutput(this, rect, -1, parent ? parent : guienv->getRootGUIElement());
                output.push_back(out);
                out->grab();
            return out;
        }
        void IGUIInputOutputContext::removeInput(IGUIInput *in)
        {
            for(u32 i = 0; i<input.size(); ++i)
            {
                if(input[i] == in)
                {
                    input.erase(i);
                    in->drop();
                }
            }
        }
        void IGUIInputOutputContext::removeOutput(IGUIOutput *out)
        {
            for(u32 i = 0; i<input.size(); ++i)
            {
                if(input[i]->getLink() == out)
                {
                    input[i]->setLink(0);
                }
            }
            for(u32 i = 0; i<output.size(); ++i)
            {
                if(output[i] == out)
                {
                    output.erase(i);
                    out->drop();
                }
            }
        }
        void IGUIInputOutputContext::drawSpline(core::vector2di from, core::vector2di to, video::SColor color)
        {
            core::vector2di last = from;
            for(f32 x = 0.f; x<1.f; x+=0.13f)
            {
                core::vector2di spline;
                    f32 k = (1-cosf(x*core::PI))/2;
                    spline.Y = from.Y*(1-k)+to.Y*k; //cos
                    spline.X = from.X+x*(to.X-from.X);
                    guienv->getVideoDriver()->draw2DLine(spline, last, color);
                last = spline;
            }
            guienv->getVideoDriver()->draw2DLine(last, to, color);
        }
    }
}
