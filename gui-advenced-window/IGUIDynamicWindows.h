#ifndef IGUIDYNAMICWINDOWS_H
#define IGUIDYNAMICWINDOWS_H

#include <irrlicht/IGUIWindow.h>

namespace irr
{
    class IrrlichtDevice;
    namespace gui
    {
        class IGUIDynamicWindows : public IGUIWindow
        {
            public:
                IGUIDynamicWindows(IrrlichtDevice*, core::recti, u32);
                virtual ~IGUIDynamicWindows();

                virtual bool OnEvent(const SEvent& event);

                virtual IGUIButton* getCloseButton() const;
                virtual IGUIButton* getMinimizeButton() const;
                virtual IGUIButton* getMaximizeButton() const;

                virtual void setSmoothTime(u32);
                virtual void setDraggable(bool draggable);
                virtual void setDrawBackground(bool draw);
                virtual bool getDrawBackground() const;
                virtual void setDrawTitlebar(bool draw);
                virtual bool getDrawTitlebar() const;
                virtual u32 getSmoothTime();

                virtual core::recti getClientRect() const;

                virtual bool isDraggable() const;

                virtual void move(core::position2di absoluteMovement);

                virtual void draw();
            protected:
                virtual void updateClientRect();
                virtual void refreshSprites();


                bool IsActive, Dragging, IsDraggable, DrawBackground, DrawTitlebar, Moving;

                u32 StartTime;
                u32 SmoothTime;

                core::line2di Drag;

                video::SColor CurrentIconColor;
                core::recti ClientRect;

                IGUIButton *MinButton;
                IGUIButton *RestoreButton;
                IGUIButton *CloseButton;
                IrrlichtDevice  *dev;
        };
    }
}

#endif // IGUIDYNAMICWINDOWS_H
