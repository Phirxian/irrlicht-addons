#include "CGridSceneNode.h"
#include "ISceneManager.h"
#include "IVideoDriver.h"

namespace irr
{
    namespace scene
    {
        CGridSceneNode::CGridSceneNode(ISceneNode* parent, ISceneManager* smgr, s32 id,
                u32 spacing, u32 size, video::SColor gridcolor, u32 accentlineoffset,
                video::SColor accentgridcolor, bool axislinestate)  : ISceneNode(parent, smgr, id),
                m_spacing(spacing), m_size(size),
                m_gridcolor(gridcolor), m_accentgridcolor(accentgridcolor),
                m_accentlineoffset(accentlineoffset), m_AxisLineState(axislinestate),
                m_XLineColor(video::SColor(255,255,0,0)),
                m_ZLineColor(video::SColor(255,0,0,255)),
                m_YLineColor(video::SColor(255,0,255,0))
        {
            // Set the material
            Buffer.Material.Wireframe = false;
            Buffer.Material.Lighting = false;
            Buffer.Material.Thickness = 1;
            Buffer.Material.FogEnable = false;
            Buffer.Material.ZWriteEnable = false;
            Buffer.Material.BackfaceCulling = true;
            Buffer.Material.AntiAliasing = true;

            // Set the default culling state to Frustum Box
            AutomaticCullingState = EAC_FRUSTUM_BOX;

            RegenerateGrid();
        }

        CGridSceneNode* CGridSceneNode::clone(ISceneNode *newParent, ISceneManager *newSceneManager)
        {
            if (!newParent) newParent = Parent;
            if (!newSceneManager) newSceneManager = SceneManager;

            CGridSceneNode* clone = new CGridSceneNode(
                Parent,
                SceneManager,
                ID,
                m_spacing,
                m_size*2,
                m_gridcolor,
                m_accentlineoffset,
                m_accentgridcolor,
                m_AxisLineState);

            if (!clone)
                return 0x0;

            clone->SetAxisLineXColor(m_XLineColor);
            clone->SetAxisLineZColor(m_ZLineColor);
            clone->SetMaterial(Buffer.Material);

            clone->drop();
            return clone;
        }

        void CGridSceneNode::OnRegisterSceneNode()
        {
            if (IsVisible)
                SceneManager->registerNodeForRendering(this);

            ISceneNode::OnRegisterSceneNode();
        }

        void CGridSceneNode::RegenerateGrid()
        {
            //Clean up memory
            Buffer.Indices.clear();
            Buffer.Vertices.clear();

            u32 m_numVertices = ((m_size / m_spacing) + 1) * 2 * 2;
            if (m_accentlineoffset) m_numVertices += ((m_size / (m_spacing * m_accentlineoffset)) + 1) * 2 * 2;

            if ( m_numVertices > 65535)
            {
                //Too many vertices on 16 bit for for 16bit indices of SMeshBuffer
                //Returning with a blank buffer to avoid segfaulting the entire application
                return;
            }

            //Set our left corner
            core::vector3df leftMost = core::vector3df(0,0,0);
            leftMost.X -= m_size/2;
            leftMost.Z -= m_size/2;

            //Set our right corner
            core::vector3df rightMost = core::vector3df(0,0,0);
            rightMost.X += m_size/2;
            rightMost.Z += m_size/2;

            u32 indexIndex = 0;

            //X-axis lines
            for (u32 x = 0; x <= m_size; x+= m_spacing)
            {
                core::vector3df start = leftMost;
                start.X += x ;

                core::vector3df end = rightMost;
                end.X = start.X;

                Buffer.Vertices.push_back(video::S3DVertex(start, core::vector3df(0,1,0), m_gridcolor, core::vector2df(0.0f, 0.0f)));
                Buffer.Vertices.push_back(video::S3DVertex(end, core::vector3df(0,1,0), m_gridcolor, core::vector2df(0.0f, 0.0f)));

                Buffer.Indices.push_back(indexIndex++);
                Buffer.Indices.push_back(indexIndex++);
            }

            //Z-axis lines
            for (u32 z = 0; z <= m_size; z+= m_spacing)
            {
                core::vector3df start = leftMost;
                start.Z += z ;

                core::vector3df end = rightMost;
                end.Z = start.Z;

                Buffer.Vertices.push_back(video::S3DVertex(start, core::vector3df(0,1,0), m_gridcolor, core::vector2df(0.0f, 0.0f)));
                Buffer.Vertices.push_back(video::S3DVertex(end, core::vector3df(0,1,0), m_gridcolor, core::vector2df(0.0f, 0.0f)));

                Buffer.Indices.push_back(indexIndex++);
                Buffer.Indices.push_back(indexIndex++);
            }

            //Accent lines are only drawn if the offset is greater than 0
            if (m_accentlineoffset > 0)
            {
                //X-axis
                for (u32 x = 0; x <= m_size; x+= m_spacing*m_accentlineoffset)
                {
                    core::vector3df start = leftMost;
                    start.X += x ;

                    core::vector3df end = rightMost;
                    end.X = start.X;

                    Buffer.Vertices.push_back(video::S3DVertex(start, core::vector3df(0,1,0), m_accentgridcolor, core::vector2df(0.0f, 0.0f)));
                    Buffer.Vertices.push_back(video::S3DVertex(end, core::vector3df(0,1,0), m_accentgridcolor, core::vector2df(0.0f, 0.0f)));

                    Buffer.Indices.push_back(indexIndex++);
                    Buffer.Indices.push_back(indexIndex++);
                }

                //Z-axis
                for (u32 z = 0; z <= m_size; z+= m_spacing*m_accentlineoffset)
                {
                    core::vector3df start = leftMost;
                    start.Z += z ;

                    core::vector3df end = rightMost;
                    end.Z = start.Z;
                    Buffer.Vertices.push_back(video::S3DVertex(start, core::vector3df(0,1,0), m_accentgridcolor, core::vector2df(0.0f, 0.0f)));
                    Buffer.Vertices.push_back(video::S3DVertex(end, core::vector3df(0,1,0), m_accentgridcolor, core::vector2df(0.0f, 0.0f)));

                    Buffer.Indices.push_back(indexIndex++);
                    Buffer.Indices.push_back(indexIndex++);
                }
            }


            // Create our box, it is the size of the grid exactly, plus 1 in the Y axis
            Buffer.BoundingBox = core::aabbox3df(-(f32)m_size/2,-0.5f,-(f32)m_size/2,(f32)m_size/2,0.5f,(f32)m_size/2);
        }

        void CGridSceneNode::render()
        {
            video::IVideoDriver* driver = SceneManager->getVideoDriver();

            //Prep to render
            if (driver)
            {
                driver->setMaterial(Buffer.Material);
                driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

                driver->drawVertexPrimitiveList(
                    Buffer.Vertices.pointer(),
                    Buffer.Vertices.size(),
                    Buffer.Indices.pointer(),
                    Buffer.Vertices.size()/2,
                    video::EVT_STANDARD,
                    scene::EPT_LINES
                );

                // Axis Lines are only drawn if the State is true
                if (m_AxisLineState)
                {
                    Buffer.Material.Thickness = 3;
                    driver->setMaterial(Buffer.Material);
                    driver->draw3DLine(core::vector3df(0,0,0),core::vector3df(0.5f,0,0), m_XLineColor);
                    driver->draw3DLine(core::vector3df(0,0,0),core::vector3df(0,0.5f,0), m_YLineColor);
                    driver->draw3DLine(core::vector3df(0,0,0),core::vector3df(0,0,0.5f), m_ZLineColor);
                    Buffer.Material.Thickness = 1;
                    driver->setMaterial(Buffer.Material);
                }
            }
        }

        const core::aabbox3d<f32>& CGridSceneNode::getBoundingBox() const
        {
            return Buffer.BoundingBox;
        }

        u32 CGridSceneNode::getMaterialCount()
        {
            return 1;
        }

        video::SMaterial& CGridSceneNode::getMaterial(u32 i)
        {
            return Buffer.Material;
        }

        u32 CGridSceneNode::GetSpacing()
        {
            return m_spacing;
        }

        u32 CGridSceneNode::GetSize()
        {
            return m_size;
        }

        u32 CGridSceneNode::GetAccentlineOffset()
        {
            return m_accentlineoffset;
        }

        video::SColor CGridSceneNode::GetAccentlineColor()
        {
            return m_accentgridcolor;
        }

        video::SColor CGridSceneNode::GetGridColor()
        {
            return m_gridcolor;
        }

        bool CGridSceneNode::AreAxisLineActive()
        {
            return m_AxisLineState;
        }

        video::SColor CGridSceneNode::GetAxisLineXColor()
        {
            return m_XLineColor;
        }

        video::SColor CGridSceneNode::GetAxisLineZColor()
        {
            return m_ZLineColor;
        }

        void CGridSceneNode::SetSpacing(u32 newspacing)
        {
            m_spacing = newspacing;
            RegenerateGrid();
        }

        void CGridSceneNode::SetSize(u32 newsize)
        {
            m_size = newsize;
            RegenerateGrid();
        }

        void CGridSceneNode::SetAccentlineColor(video::SColor newcolor)
        {
            m_accentgridcolor = newcolor;
            RegenerateGrid();
        }

        void CGridSceneNode::SetAccentlineOffset(u32 newoffset)
        {
            m_accentlineoffset = newoffset;
            RegenerateGrid();
        }

        void CGridSceneNode::SetGridColor(video::SColor newcolor)
        {
            m_gridcolor = newcolor;
            RegenerateGrid();
        }

        void CGridSceneNode::SetAxisLineActive(bool active)
        {
            m_AxisLineState = active;
        }

        void CGridSceneNode::SetAxisLineXColor(video::SColor XLine)
        {
            m_XLineColor = XLine;
        }

        void CGridSceneNode::SetAxisLineZColor(video::SColor ZLine)
        {
            m_ZLineColor = ZLine;
        }

        void CGridSceneNode::SetMaterial(video::SMaterial newMaterial)
        {
            Buffer.Material = newMaterial;
        }
    }
}
