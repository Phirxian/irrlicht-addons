#ifndef IRR_GUI_INPUT_OUTPUT_CONTEXT
#define IRR_GUI_INPUT_OUTPUT_CONTEXT

#include "IGUIInput.h"
#include "IGUIOutput.h"

namespace irr
{
    class IrrlichtDevice;
    namespace gui
    {
        class IGUIInputOutputContext
        {
            public:
                IGUIInputOutputContext(IrrlichtDevice *);

                bool OnEvent(const SEvent &event);

                IGUIInput* addInput(core::recti, IGUIElement *parent = 0);
                IGUIOutput* addOutput(core::recti, IGUIElement *parent = 0);

                void removeInput(IGUIInput*);
                void removeOutput(IGUIOutput*);

                core::array<IGUIInput*> input;
                core::array<IGUIOutput*> output;

                IrrlichtDevice *device;
                IGUIEnvironment *guienv;

                void drawSpline(core::vector2di, core::vector2di, video::SColor);
            protected:
            private:
        };
    }
}
#endif
