#ifndef __C_GUI_ROUND_PROGRESS_HEADER__
#define __C_GUI_ROUND_PROGRESS_HEADER__

#include <irrlicht/IGUIElement.h>
#include <irrlicht/ITexture.h>
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/SMaterial.h>
#include <irrlicht/S3DVertex.h>
#include <irrlicht/irrList.h>

/**
 * Copyright (C) <2014> <Jehan-antoine vayssade>
 * Ovan/Magun contact on irrlicht-fr.org or ovan@sleek-think.ovh
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
**/

namespace irr
{
    namespace gui
    {
        struct CGUIPieChartElement
        {
            public:
                CGUIPieChartElement(float from = 0.f, float to = 1.f, const video::SColor &c = {255, 255, 255, 255}, float depth = 0.f);

                void set(float from, float to);
                void setDepth(float depth = 0.f);
                void setColor(const video::SColor&);
            public:
                video::SColor clr;
                float from, to, depth;
                core::array<core::triangle3df> pos;
            private:
                void calc(float from, float to);
                core::vector3df calc(float);
            private:
                friend class CGUIPieChart;
        };
        class CGUIPieChart : public IGUIElement
        {
            public:
                CGUIPieChart(IGUIEnvironment *environment, IGUIElement *parent, const core::recti &size, s32 id = 0) noexcept;
                ~CGUIPieChart() noexcept;

                virtual void add(const CGUIPieChartElement&);
                virtual CGUIPieChartElement& get(int);
                virtual bool erase(int);
                virtual int count() const;

                virtual void setBackgroundColor(const video::SColor&);
                virtual void setBackgroundTexture(video::ITexture*);
                virtual void setForegroundTexture(video::ITexture*);

                virtual video::ITexture* getBackgroundTexture() const;
                virtual video::ITexture* getForegroundTexture() const;
                virtual video::SColor    getBackgroundColor() const;

                virtual void updateAbsolutePosition();

                virtual void draw();
            protected:
                video::IVideoDriver *driver;
                core::list<CGUIPieChartElement> item;
            private:
                video::SColor clr;
                core::array<u16> idx;
                core::array<video::S3DVertex> vtx;
                video::ITexture *bg, *fg;
                video::SMaterial mat;
        };
    }
}

#endif
