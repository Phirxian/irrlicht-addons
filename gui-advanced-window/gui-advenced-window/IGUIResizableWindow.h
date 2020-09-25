#ifndef _I_GUI_RESIZABLE_H_
#define _I_GUI_RESIZABLE_H_

#include <irrlicht/IGUIWindow.h>

namespace irr
{
    namespace gui
    {
        class IGUIButton;
        class IGUIResizableWindow : public IGUIWindow
        {
            public:
                IGUIResizableWindow(IGUIEnvironment* environment, core::recti rectangle, IGUIElement *parent);
                ~IGUIResizableWindow();

                virtual const c8* getTypeName() const { return "IGUIResizableWindow"; }

                virtual void setDraggable(bool draggable);
                virtual void setDrawBackground(bool draw);
                virtual void setDrawTitlebar(bool draw);

                virtual IGUIButton* getCloseButton() const;
                virtual IGUIButton* getMinimizeButton() const;
                virtual IGUIButton* getMaximizeButton() const;
                virtual IGUIButton* getResizeButton() const;

                virtual bool getDrawBackground() const;
                virtual bool getDrawTitlebar() const;

                virtual bool isDraggable() const;

                virtual core::recti getClientRect() const;

                virtual bool OnEvent(const SEvent &event);

                virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;
                virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

                virtual void draw();
            protected:
                bool Dragging, IsDraggable, Resizing;
                bool DrawBackground, DrawTitlebar;
                bool IsActive;

                core::position2di DragStart;
                core::recti ClientRect;
                video::SColor CurrentIconColor;

                IGUIButton *ResizeButton;
                IGUIButton *CloseButton;
                IGUIButton *MinButton;
                IGUIButton *RestoreButton;

                void updateClientRect();
                void refreshSprites();
            private:
        };
    }
}

#endif // _I_GUI_RESIZABLE_H_

