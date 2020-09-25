#ifndef __C_GRID_SCENE_NODE_H__
#define __C_GRID_SCENE_NODE_H__

#include <ISceneNode.h>
#include <CMeshBuffer.h>
#include <memory>

//! Grid scene node
/*! If you need a grid on the XY or ZY axis, simply rotate this node by 90
degrees in the appropiate axis.
This node creates an XZ grid by default, which should be fine for normal use.
Axis Lines are a default Red and Blue for the X and Z axis respectively.

Please note that the internal meshbuffer used for the grid has a max size of 65535 indecies.

Thanks goes to MasterGod for helping to clean up the code and for a few bug fixes.

Additional thanks to:
JP for optimising the rendering.
Vins for fixing a nasty crash bug and optimising memory usage.
*/

namespace irr
{
    namespace scene
    {
        class CGridSceneNode : public ISceneNode
        {
            public:
                //! Constructor
                CGridSceneNode(ISceneNode* parent, ISceneManager* smgr, s32 id = -1,
                    u32 spacing = 8, u32 size = 1024, video::SColor gridcolor = video::SColor(255,128,128,128),
                    u32 accentlineoffset = 8, video::SColor accentgridcolor = video::SColor(255,192,192,192),
                    bool axislinestate = false);

                //! Will create a copy of this scenenode and it's settings
                virtual CGridSceneNode* clone(ISceneNode* newParent = 0, ISceneManager* newSceneManager = 0);

                //! Pre-Register stuff
                virtual void OnRegisterSceneNode();

                //! Render our grid using 3D lines stored inside the internal meshbuffer
                virtual void render();

                //! Returns our bounding box
                virtual const core::aabbox3d<f32>& getBoundingBox() const;

                //! Returns the total number of materials, in this case, only 1
                virtual u32 getMaterialCount();

                //! Returns the only material
                virtual video::SMaterial& getMaterial(u32 i);

                //! Will cause the grid scene node to rebuild it's grid
                void RegenerateGrid();

                //! Returns the Spacing of the grid
                u32 GetSpacing();

                //! Returns the total size of the grid
                u32 GetSize();

                //! Returns the Grid Color
                video::SColor GetGridColor();

                //! Returns the offset of the accent lines
                u32 GetAccentlineOffset();

                //! Returns the Accent Line Color
                video::SColor GetAccentlineColor();

                //! Returns the Active State of the Axis Lines
                bool AreAxisLineActive();

                //! Returns the Color of the "X" axis lines
                video::SColor GetAxisLineXColor();

                //! Returns the Color of the "Z" axis lines
                video::SColor GetAxisLineZColor();

                //! Sets Spacing
                void SetSpacing(u32 newspacing);

                //! Sets Size
                void SetSize(u32 newsize);

                //! Sets the general grid color
                void SetGridColor(video::SColor newcolor);

                //! Sets the offset for the accent lines
                //! If > 0, accent lines will be active, otherwise not
                void SetAccentlineOffset(u32 newoffset);

                //! Sets the color of the accent lines
                void SetAccentlineColor(video::SColor newcolor);

                //! Sets whether the lines denoting the center of the grid are active
                void SetAxisLineActive(bool active);

                //! Sets the Color of the "X" axis lines
                void SetAxisLineXColor(video::SColor XLine);

                //! Sets the Color of the "Z" axis lines
                void SetAxisLineZColor(video::SColor ZLine);

                //! Allows for setting a complete new material
                void SetMaterial(video::SMaterial newMaterial);

            private:
                u32 m_spacing;
                u32 m_size;
                video::SColor m_gridcolor;
                video::SColor m_accentgridcolor;
                u32 m_accentlineoffset;
                bool m_AxisLineState;
                video::SColor m_XLineColor;
                video::SColor m_YLineColor;
                video::SColor m_ZLineColor;

                irr::scene::SMeshBuffer Buffer;
        };
    }
}

#endif
