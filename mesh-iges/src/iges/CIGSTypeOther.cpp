#include "CIGSMeshLoader.h"
#include "CIGSType.h"

namespace irr
{
    namespace scene
    {
        template<> //! Null
        void IgsBluidData<0>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#0 Null (%s)\n", e.parameter.c_str());
        }
        template<> //! Point
        void IgsBluidData<116>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * A point is defined by its coordinates (X, Y, Z)
             */

            irr::core::vector3df pos;
            irr::s32 last = 0, cursor = 0;

            readNextFloat(pos.X, e, t[4], cursor, last, t);
            readNextFloat(pos.Y, e, t[4], cursor, last, t);
            readNextFloat(pos.Z, e, t[4], cursor, last, t);

//            float PTR;
//            readNextFloat(PTR, e, t[4], cursor, last, t);

            printf("#116 Point (%f, %f, %f)\n", pos.X, pos.Y, pos.Z);

            igs_transformation.transformVect(pos, pos);

            auto data = (irr::scene::SMeshBuffer*)out->getMesh(IGS_POINT)->getMeshBuffer(
                out->getMesh(IGS_POINT)->getMeshBufferCount()-1
            );

            data->Vertices.push_back({pos.X, pos.Y, pos.Z, 0.f, 0.f, 0.f, e.irrColor, 0.f, 0.f});
            data->Indices.push_back(data->Indices.size());
        }
        template<> //! Direction
        void IgsBluidData<123>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * A direction entity is a nonzero vector in 3D that is defined by its three components
             * with respect to the coordinate axe. The normal vector of surface can be determined
             * by this entity
             */

            irr::core::vector3df pos;
            irr::s32 last = 0, cursor = 0;

            readNextFloat(pos.X, e, t[4], cursor, last, t);
            readNextFloat(pos.Y, e, t[4], cursor, last, t);
            readNextFloat(pos.Z, e, t[4], cursor, last, t);

            printf("#123 Direction (%f, %f, %f)\n", pos.X, pos.Y, pos.Z);
        }
        template<> //! Transformation Matrix
        void IgsBluidData<124>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * This entity can give the relative location information between two coordinate
             * system Xo, Yo, Zo coordinate system and Xt, Yt, Zt coordinate system
             *
             *  [R11 R12 R13]   [Xo]   [T1]   [Xt]        |R11 R12 R13|
             *  [R21 R22 R23] x [Yo] + [T2] = [Yt]  where |R21 R22 R23| = 1
             *  [R31 R32 R33]   [Zo]   [T3]   [Zt]        |R31 R32 R33|
             */

            irr::s32 last = 0, cursor = 0;

            //! top rotation matrix
            readNextFloat(igs_transformation[0], e, t[4], cursor, last, t);
            readNextFloat(igs_transformation[1], e, t[4], cursor, last, t);
            readNextFloat(igs_transformation[2], e, t[4], cursor, last, t);

            //! translation X
            readNextFloat(igs_transformation[12], e, t[4], cursor, last, t);

            //! middle rotation matrix
            readNextFloat(igs_transformation[4], e, t[4], cursor, last, t);
            readNextFloat(igs_transformation[5], e, t[4], cursor, last, t);
            readNextFloat(igs_transformation[6], e, t[4], cursor, last, t);

            //! translation Y
            readNextFloat(igs_transformation[13], e, t[4], cursor, last, t);

            //! bottom rotation matrix
            readNextFloat(igs_transformation[8], e, t[4], cursor, last, t);
            readNextFloat(igs_transformation[9], e, t[4], cursor, last, t);
            readNextFloat(igs_transformation[10], e, t[4], cursor, last, t);

            //! translation Z
            readNextFloat(igs_transformation[14], e, t[4], cursor, last, t);

            printf("#124 transformation matrix\n");
        }
        template<> //! Annotation
        void IgsBluidData<202>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#202 Annotation\n");
        }
        template<> //! Text
        void IgsBluidData<212>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(000) : ...
             * form(001) : dual-stack dimension
             * form(002) : imbedded font change dimension
             * form(003) : superscripted dimension
             * form(004) : subscripted dimension
             * form(005) : superscripted/subscripted dimension
             * form(006) : multiple stack - left justified
             * form(007) : multiple stack - center justified
             * form(008) : multiple stack - right justified
             * form(100) : simple fractional dimension
             * form(101) : dual stack fractional dimension
             * form(102) : imbedded font change/double fractional dimension
             * form(105) : super-/sub-scripted fractional dimension
             */
            int last = e.parameter.findLast(t[4]);
            printf("#212 Text (%d) : %s\n", e.form, e.parameter.subString(last, e.parameter.size() - last).c_str());
        }
        template<> //! Leader/Arrow
        void IgsBluidData<214>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * http://www.wiz-worx.com/iges5x/wysiwyg/f214x.shtml
             * use a special texture ?
             *
             * form(00) : ...
             * form(01) : Wedge
             * form(02) : Triangle
             * form(03) : Filled Triangle
             * form(04) : No Arrowhead
             * form(05) : Circle
             * form(06) : Filled Circle
             * form(07) : Rectangle
             * form(08) : Filled Rectangle
             * form(09) : Slash
             * form(10) : Integral Sign
             * form(11) : Open Triangle
             * form(12) : Dimension Origin
             */
            printf("#214 Leader/Arrow (%d) : TODO\n", e.form);
        }
        template<> //! Linear Dimension
        void IgsBluidData<216>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(00) : ...
             * form(01) : Diameter
             * form(02) : Radius
             */
            printf("#216 Linear Dimension (%d) : TODO\n", e.form);
        }
        template<> //! Ordinate Dimension
        void IgsBluidData<218>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(00) : Ordinate dimension
             * form(01) : Ordinate dimension with datum
             */
            printf("#218 Ordinate Dimension (%d) : TODO\n", e.form);
        }
        template<> //! Point dimension
        void IgsBluidData<220>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#220 Point Dimension : TODO\n");
        }
        template<> //! Radius dimension
        void IgsBluidData<222>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(0) : Radius dimension
             * form(1) : Radius dimension/multiple leader
             */
            printf("#222 Radius Dimension (%d) : TODO\n", e.form);
        }
        template<> //! General symbol
        void IgsBluidData<228>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(0) : General symbol
             * form(1) : Datum feature symbol
             * form(2) : Datum target symbol
             * form(3) : Feature control frame
             */
            printf("#228 General symbol (%d) : TODO\n", e.form);
        }
        template<> //! Sectioned area
        void IgsBluidData<230>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(0) : Sectioned area (Standard Crosshatching)
             * form(1) : Sectioned area (Inverted Crosshatching)
             */
            printf("#230 Sectioned area (%d) : TODO\n", e.form);
        }
        template<> //! Subfigure Definition
        void IgsBluidData<308>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#308 Subfigure Definition : TODO\n");
        }
        template<> //! Associativity Instance
        void IgsBluidData<402>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(3) : "Views Visible"
             * form(4) : "Views Visible, Color, Line Weight"
             * form(7) : "Unordered Group Without Back Pointers"
             */
            printf("#402 Associativity Instance (%d) : TODO\n", e.form);
        }
        template<> //! drawing
        void IgsBluidData<404>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(0) : "Normal Drawing"
             */
            printf("#404 Drawing (%d) : TODO\n", e.form);
        }
        template<> //! drawing
        void IgsBluidData<406>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(15) : name
             * form(16) : size
             * form(17) : units
             */
            printf("#406 Drawing (%d) : TODO\n", e.form);
        }
        template<> //! View
        void IgsBluidData<410>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * @see http://what-when-how.com/computer-graphics-and-geometric-modeling/iges-computer-graphics-and-geometric-modeling-part-2/
             * form(0) : "Orthogonal"
             * other "Perspective" ?
             */
            printf("#410 View (%d) : TODO\n", e.form);
        }
    }
}
