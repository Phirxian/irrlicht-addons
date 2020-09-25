#ifndef IRR_GUI_OUTPUT
#define IRR_GUI_OUTPUT

#include <irrlicht/IGUIElement.h>

namespace irr
{
    namespace gui
    {
        class IGUIInputOutputContext;
        class IGUIInput;

        class IGUIOutput : public IGUIElement
        {
            public:
                IGUIOutput(IGUIInputOutputContext*,core::recti rectangle, s32 id = -1, IGUIElement *parent = 0);
                virtual ~IGUIOutput();

                virtual void setTexture(video::ITexture *i);
                virtual video::ITexture* getTexture();

                virtual void setUserData(void*);
                virtual void*getUserData();

                virtual bool isHovored();
                virtual bool isOnSelection();

                virtual bool OnEvent(const SEvent &event);
                virtual void draw();
            protected:
                bool selected;
                bool hovored;

                core::vector2di cursor;
                core::recti ImageRect;
                video::SColor color;

                video::ITexture *texture;
                IGUIInputOutputContext *context;

                void *user;
            private:
                friend class IGUIInputOutputContext;
        };
    }
}
#endif
