#ifndef IRR_GUI_INPUT
#define IRR_GUI_INPUT

#include <irrlicht/IGUIElement.h>

namespace irr
{
    namespace gui
    {
        class IGUIInputOutputContext;
        class IGUIOutput;
        class IGUIInput : public IGUIElement
        {
            public:
                IGUIInput(IGUIInputOutputContext*,core::recti rectangle, s32 id = -1, IGUIElement *parent = 0);
                virtual ~IGUIInput();

                virtual void setTexture(video::ITexture *i);
                virtual video::ITexture* getTexture();

                virtual bool OnEvent(const SEvent &event);
                virtual bool isHovored();

                virtual void setLink(IGUIOutput*);
                virtual IGUIOutput *getLink();

                virtual void draw();
            protected:
                bool hovored;
                virtual void setSlotTexture(video::ITexture *i);
                virtual video::ITexture* getSlotTexture();

                core::vector2di cursor;
                core::recti ImageRect;
                video::SColor color;

                IGUIOutput *link;
                video::ITexture *texture, *slot;
                IGUIInputOutputContext *context;
        };
    }
}
#endif
