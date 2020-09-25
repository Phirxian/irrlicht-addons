#include "CIGSMeshLoader.h"
#include "CIGSType.h"

namespace irr
{
    namespace scene
    {
        template<> //! parametric spline surface curve
        void IgsBluidData<114>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * The parametric spline surface is a grid of parametric polynomial patches.
             * The type of the surface is represented in the parameter date entry section
             */
            printf("#114 parametric spline surface curve : TODO\n");
        }
        template<> //! ruled surface
        void IgsBluidData<118>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * A ruled surface is formed by moving a line connecting points of equal relative arc
             * length or equal relative parametric value on two parametric curves from a start
             * to a end point on the curve
             */
            printf("#118 ruled surface : TODO\n");
        }
        template<> //! surface of revolution
        void IgsBluidData<120>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * A surface is created by rotating the generatrix about the axis of rotation
             * from the start to the terminated position. The axis of rotation is a line entity
             * The generatrix may be a conic arc, line, circular arc, or composite curve
             * The angles of rotation are counterclockwize about the positive direction of rotation axis
             */
            printf("#120 surface of revolution : TODO\n");
        }
        template<> //! tabulated cylinder
        void IgsBluidData<122>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * A tabulated cylinder is a surface formed by moving a line segment called
             * the generatrix parallel to itself along a curve called the directrix.
             * The curve may be a line, circular arc, etc
             */
            printf("#122 tabulated cylinder : TODO\n");
        }
        template<> //! Rational B-Spline Surface
        void IgsBluidData<128>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
                form(0) : ...
                form(1) : Plane
                form(2) : Right circular cylinder
                form(3) : Cone
                form(4) : Sphere
                form(5) : Torus
                form(6) : Surface of Revolution
                form(7) : Tabulated cylinder
                form(8) : Ruled surface
                form(9) : General quadric surface
            */
            printf("#128 Rational B-Spline Surface (%d) : TODO\n", e.form);
        }
        template<> //! Offset Surface
        void IgsBluidData<140>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#140 Offset Surface : TODO\n");
        }
        template<> //! Curve on a Parametric Surface
        void IgsBluidData<142>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#142 Curve on a Parametric Surface : TODO\n");
        }
        template<> //! Bounded Surface
        void IgsBluidData<143>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#143 Bounded Surface : TODO\n");
        }
        template<> //! Trimmed (Parametric) Surface
        void IgsBluidData<144>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#144 Trimmed (Parametric) Surface : TODO\n");
        }
        template<> //! Sphere
        void IgsBluidData<158>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#158 Sphere : TODO\n");
        }
        template<> //! Manifold Solid B-Rep Object
        void IgsBluidData<186>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#186 Manifold Solid B-Rep Object : TODO\n");
        }
        template<> //! plane
        void IgsBluidData<190>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * the plane surface is defined by a point on the plane
             * and the normal direction to the surface
             */
            irr::core::vector3df pos, nor;
            irr::s32 last = 0, cursor = 0;

            readNextFloat(pos.X, e, t[4], cursor, last, t);
            readNextFloat(pos.Y, e, t[4], cursor, last, t);
            readNextFloat(pos.Z, e, t[4], cursor, last, t);

            readNextFloat(nor.X, e, t[4], cursor, last, t);
            readNextFloat(nor.Y, e, t[4], cursor, last, t);
            readNextFloat(nor.Z, e, t[4], cursor, last, t);

            igs_transformation.transformVect(pos, pos);

            printf(
                "#190 Plane pos(%f, %f, %f) normal(%f, %f, %f) : TODO\n",
                pos.X, pos.Y, pos.Z, nor.X, nor.Y, nor.Z
            );

            //! TODO
        }
        template<> //! Right Circular Cylindrical Surface
        void IgsBluidData<192>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * The right circular cylinder surface is defined by a point on the axis
             * of the cylinder, the direction of the axis of the cylinder and a radius
             */
            printf("#192 Right Circular Cylindrical Surface : TODO\n");
        }
        template<> //! Right Circular Conical Surface
        void IgsBluidData<194>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#194 Right Circular Conical Surface : TODO\n");
        }
        template<> //! Spherical Surface
        void IgsBluidData<196>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            auto data = (irr::scene::SMeshBuffer*)out->getMesh(IGS_SURFACE)->getMeshBuffer(
                out->getMesh(IGS_SURFACE)->getMeshBufferCount()-1
            );

            //auto *mesh = smgr->getGeometryCreator()->createSphereMesh();
            //move meshbuffer to data and delete mesh

            printf("#196 Spherical Surface : TODO\n");
        }
        template<> //! Toroidal Surface
        void IgsBluidData<198>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            auto data = (irr::scene::SMeshBuffer*)out->getMesh(IGS_SURFACE)->getMeshBuffer(
                out->getMesh(IGS_SURFACE)->getMeshBufferCount()-1
            );

            //auto *mesh = smgr->getGeometryCreator()->?
            //move meshbuffer to data and delete mesh

            printf("#198 Toroidal Surface : TODO\n");
        }
        template<> //! Singular Subfigure Instance
        void IgsBluidData<408>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#408 Singular Subfigure Instance : TODO\n");
        }
        template<> //! Vertex List
        void IgsBluidData<502>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * This entity is used to determine the vertex list that contains all the
             * vertexes of the object.
             */
            printf("#502 Vertex List : TODO\n");
        }
        template<> //! Edge List
        void IgsBluidData<504>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * This entity is used to determine the edge list that contains all the
             * edges of the object.
             */
            printf("#504 Edge List : TODO\n");
        }
        template<> //! Loop
        void IgsBluidData<508>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * This entity is used to determine the loops that are involved in all faces
             * of the object
             */
            printf("#508 Loop : TODO\n");
        }
        template<> //! Faces
        void IgsBluidData<510>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * This entity is used to determine the faces that comprise the object.
             */
            printf("#510 Faces : TODO\n");
        }
        template<> //! Shell
        void IgsBluidData<514>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * The shell is represented as a set of edge connected and oriented faces.
             * The normal of the shell is in the seme direction as the normal of the face.
             */
            printf("#514 Shell : TODO\n");
        }
    }
}
