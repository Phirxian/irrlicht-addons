#include "CGUIRoundProgress.h"

#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/S3DVertex.h>
#include <irrlicht/irrMath.h>
#include <irrlicht/SColor.h>

namespace irr
{
    namespace gui
    {
        CGUIRoundProgress::CGUIRoundProgress(IGUIEnvironment *environment, IGUIElement *parent, const core::recti &size, s32 id) noexcept
            : IGUIElement(EGUIET_ELEMENT , environment, parent, id, size),
              idx{0,  2,  1, 3,  4,  5, 6,  8,  7, 9, 10, 11},
              bg(0), fg(0), clr{255, 255, 255, 255},
              driver(environment->getVideoDriver())
        {
            mat.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
            mat.BackfaceCulling = false;
        }
        CGUIRoundProgress::~CGUIRoundProgress() noexcept
        {
            if(fg) fg->drop();
            if(bg) bg->drop();
        }
        void CGUIRoundProgress::setProgress(float i)
        {
            progress = irr::core::clamp(i, 0.f, 1.f);
        }
        void CGUIRoundProgress::setForegroundTexture(video::ITexture *f)
        {
            mat.setTexture(0, f);
            if(f) f->grab();
            if(fg) fg->drop();
            fg = f;
        }
        void CGUIRoundProgress::setBackgroundTexture(video::ITexture *b)
        {
            if(b) b->grab();
            if(bg) bg->drop();
            bg = b;
        }
        void CGUIRoundProgress::setColor(const irr::video::SColor &i)
        {
            clr = i;
        }
        void CGUIRoundProgress::setRotation(float i)
        {
            rotation = i;
        }
        float CGUIRoundProgress::getRotation()
        {
            return rotation;
        }
        video::SColor CGUIRoundProgress::getColor()
        {
            return clr;
        }
        video::ITexture* CGUIRoundProgress::getForegroundTexture()
        {
            return fg;
        }
        video::ITexture* CGUIRoundProgress::getBackgroundTexture()
        {
            return bg;
        }
        float CGUIRoundProgress::getProgress()
        {
            return progress;
        }
        void CGUIRoundProgress::draw()
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
            if(fg)
            {
                auto size = AbsoluteRect.getSize();
                auto &start = AbsoluteRect.UpperLeftCorner;

                irr::video::S3DVertex vtx[12]{
                    {-1.f,-1.f, 0.f, 0.f, 0.f, 1.f, clr,  0.f,  0.f}, // 0
                    {-1.f, 1.f, 0.f, 0.f, 0.f, 1.f, clr,  0.f,  1.f}, // 1
                    { 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, clr, 0.5f, 0.5f}, // 2

                    {-1.f, 1.f, 0.f, 0.f, 0.f, 1.f, clr,  0.f,  1.f}, // 3
                    { 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, clr, 0.5f, 0.5f}, // 4
                    { 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, clr,  1.f,  1.f}, // 5

                    { 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, clr, 0.5f, 0.5f}, // 6
                    { 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, clr,  1.f,  1.f}, // 7
                    { 1.f,-1.f, 0.f, 0.f, 0.f, 1.f, clr,  1.f,  0.f}, // 8

                    { 1.f,-1.f, 0.f, 0.f, 0.f, 1.f, clr,  1.f,  0.f}, // 9
                    { 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, clr, 0.5f, 0.5f}, // 10
                    {-1.f,-1.f, 0.f, 0.f, 0.f, 1.f, clr,  0.f,  0.f}  // 11
                };

                vtx[0].TCoords.Y += core::clamp((1.00f-progress)*4, 0.f, 1.f);
                vtx[3].TCoords.X += core::clamp((0.75f-progress)*4, 0.f, 1.f);
                vtx[7].TCoords.Y -= core::clamp((0.50f-progress)*4, 0.f, 1.f);
                vtx[9].TCoords.X -= core::clamp((0.25f-progress)*4, 0.f, 1.f);

                for(auto &it : vtx)
                {
                    irr::core::vector2df tmp(it.TCoords);
                    tmp.rotateBy(rotation, {0.5f, 0.5f});
                    it.Pos.X = start.X + tmp.X * size.Width;
                    it.Pos.Y = start.Y + tmp.Y * size.Height;
                }

                driver->setMaterial(mat);
                driver->draw2DVertexPrimitiveList(
                    vtx, 12, idx, 4, video::EVT_STANDARD,
                    scene::EPT_TRIANGLES, video::EIT_16BIT
                );
            }
            IGUIElement::draw();
        }
    }
}
