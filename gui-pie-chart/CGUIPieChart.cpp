#include "CGUIPieChart.h"

#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/S3DVertex.h>
#include <irrlicht/irrMath.h>
#include <irrlicht/SColor.h>
#include <iostream>

namespace irr
{
    namespace gui
    {
        CGUIPieChartElement::CGUIPieChartElement(float f, float t, const video::SColor &c, float d)
            : clr(c), depth(d)
        {
            set(f, t);
        }
        void CGUIPieChartElement::set(float f, float t)
        {
            from = f;
            to = t;
        }
        void CGUIPieChartElement::setDepth(float i)
        {
            for(int j = 0; j<pos.size(); ++j)
            {
                pos[j].pointA.Z = i;
                pos[j].pointB.Z = i;
                pos[j].pointC.Z = i;
            }
            depth = i;
        }
        void CGUIPieChartElement::setColor(const video::SColor &i)
        {
            clr = i;
        }
        core::vector3df CGUIPieChartElement::calc(float i)
        {
            core::vector3df f(0, 0, depth);

            if(i >= 0.75f && i < 1.0f)
                f.X = core::clamp((1.00f-i)*4, 0.f, 1.f);

            if(i >= 0.50f && i < 0.75f)
            {
                f.Y = core::clamp((0.75f-i)*4, 0.f, 1.f);
                f.X = 1.f;
            }

            if(i >= 0.25f && i < 0.50f)
            {
                f.Y = 1.f;
                f.X = 1.f - core::clamp((0.50f-i)*4, 0.f, 1.f);
            }

            if(i > 0.f && i <= 0.25f)
                f.Y = 1.f - core::clamp((0.25f-i)*4, 0.f, 1.f);

            return f;
        }
        void CGUIPieChartElement::calc(float from, float to)
        {
            if(to-from <= 0.0000001f)
                return;

            if(from > to || to > 1.f)
            {
                calc(from, 1.f);
                calc(0.f, to-(int)to);
                return;
            }

            float next = to;

            if(from >= 0.00f)
                next = core::min_(to, 0.25f);
            if(from >= 0.25f)
                next = core::min_(to, 0.50f);
            if(from >= 0.50f)
                next = core::min_(to, 0.75f);
            if(from >= 0.75f)
                next = core::min_(to, 1.0f);

            if(next != to)
            {
                calc(from, next);
                calc(next, to);
            }
            else
            {
                pos.push_back({
                    calc(from),
                    { 0.5f,  0.5f, depth},
                    calc(next)
                });
            }
        }
        /***************************************************/

        CGUIPieChart::CGUIPieChart(IGUIEnvironment *environment, IGUIElement *parent, const core::recti &size, s32 id) noexcept
            : IGUIElement(EGUIET_ELEMENT , environment, parent, id, size), bg(nullptr), fg(nullptr),
              driver(environment->getVideoDriver()), clr(255, 128, 128, 128)
        {
            mat.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
            mat.BackfaceCulling = false;
        }
        CGUIPieChart::~CGUIPieChart() noexcept
        {
            if(bg) bg->drop();
            if(fg) fg->drop();
        }
        void CGUIPieChart::add(const CGUIPieChartElement& i)
        {
            item.push_back(i);
        }
        CGUIPieChartElement& CGUIPieChart::get(int i)
        {
            return *(item.begin()+i);
        }
        bool CGUIPieChart::erase(int i)
        {
            if(i >= count())
                return false;

            auto it = item.begin();
                 it += i;
            item.erase(it);

            return true;
        }
        int CGUIPieChart::count() const
        {
            return item.size();
        }
        void CGUIPieChart::setForegroundTexture(video::ITexture *f)
        {
            mat.setTexture(0, f);
            if(f) f->grab();
            if(fg) fg->drop();
            fg = f;
        }
        void CGUIPieChart::setBackgroundTexture(video::ITexture *b)
        {
            if(b) b->grab();
            if(bg) bg->drop();
            bg = b;
        }
        void CGUIPieChart::setBackgroundColor(const irr::video::SColor &i)
        {
            clr = i;
        }
        video::SColor CGUIPieChart::getBackgroundColor() const
        {
            return clr;
        }
        video::ITexture* CGUIPieChart::getForegroundTexture() const
        {
            return fg;
        }
        video::ITexture* CGUIPieChart::getBackgroundTexture() const
        {
            return bg;
        }
        void CGUIPieChart::updateAbsolutePosition()
        {
            auto size = AbsoluteRect.getSize();
            auto &start = AbsoluteRect.UpperLeftCorner;

            vtx.clear();
            idx.clear();

            for(auto &it : item)
            {
                it.pos.clear();
                it.calc(it.from, it.to);
                for(int i = 0; i<it.pos.size(); ++i)
                {
                    #define imp_point(point)                            \
                    {                                                   \
                        idx.push_back(vtx.size());                      \
                        vtx.push_back({                                 \
                            start.X + it.pos[i].point.X * size.Width,   \
                            start.Y + it.pos[i].point.Y * size.Height,  \
                            it.pos[i].point.Z,                          \
                            0.f, 0.f, 1.f, it.clr,                      \
                            it.pos[i].point.X,                          \
                            it.pos[i].point.Y                           \
                        });                                             \
                    }

                    imp_point(pointA);
                    imp_point(pointB);
                    imp_point(pointC);

                    #undef imp_point
                }
            }
            IGUIElement::updateAbsolutePosition();
        }
        void CGUIPieChart::draw()
        {
            if(bg)
            {
                const video::SColor Colors[] = {clr, clr, clr, clr};
                core::rect<s32> sourceRect = core::rect<s32>(core::dimension2di(bg->getOriginalSize()));
                driver->draw2DImage(
                    bg, AbsoluteRect, sourceRect,
                    &AbsoluteClippingRect, Colors, true
                );
            }
            else
            {
                Environment->getSkin()->draw3DSunkenPane(
                    this, clr, true, true, AbsoluteRect, &AbsoluteClippingRect
                );
            }

            driver->setMaterial(mat);
            driver->draw2DVertexPrimitiveList(
                vtx.pointer(), vtx.size(),
                idx.pointer(), idx.size()/3,
                video::EVT_STANDARD,
                scene::EPT_TRIANGLES,
                video::EIT_16BIT
            );

            IGUIElement::draw();
        }
    }
}
