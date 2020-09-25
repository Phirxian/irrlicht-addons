#include "CIGSMeshLoader.h"
#include "CIGSType.h"

#include <irrMath.h>

namespace irr
{
    namespace scene
    {
        template<> //! Circular Arc
        void IgsBluidData<100>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            core::vector3df start, end, center;
            double Zt, radius;

            /*
             * To represent a circular arc in modeling space, IGES provide the information
             * including a new plane (Xt, Yt) in which the circular lies the coordinates of
             * center point, start point and terminate point.
             *
             * A new coordinates system (Xt, Yt, Zt)
             * is defined by transferring the original coodinate system (Xo, Yo, Zo)
             * via a transformation matrix and all coodinates of points (center, start, terminate)
             * related to this new coordinate system.
             *
             * The order of end points is couter-clockwize about Zt axis
             */

            {
                s32 last = 0, cursor = 0;
                readNextFloat(Zt, e, t[4], cursor, last, t);

                readNextFloat(center.X, e, t[4], cursor, last, t);
                readNextFloat(center.Y, e, t[4], cursor, last, t);
                readNextFloat(start.X, e, t[4], cursor, last, t);
                readNextFloat(start.Y, e, t[4], cursor, last, t);
                readNextFloat(end.X, e, t[4], cursor, last, t);
                readNextFloat(end.Y, e, t[4], cursor, last, t);

                center.Z = start.Z = end.Z = Zt;
                radius = start.getDistanceFrom(center);
            }

            auto data = (scene::SMeshBuffer*)out->getMesh(IGS_LINE)->getMeshBuffer(
                out->getMesh(IGS_LINE)->getMeshBufferCount()-1
            );

            {
                double Astart = atan2(start.Y - center.Y, start.X - center.X) * (180.f / core::PI);
                double Aend = atan2(end.Y - center.Y, end.X - center.X) * (180.f / core::PI);

                if(Astart < 0)    Astart += 360;
                if(Aend < 0)      Aend += 360;

                //clamp value not necessary with cos/sin
                //Astart = (int)Astart%360 + Astart - (int)Astart;
                //Aend = (int)Aend%360 + Aend - (int)Aend;

                if(Aend < Astart) Aend += 360;

                core::vector3df last = start;
                core::vector3df cur;

                igs_transformation.transformVect(last, last);

                for(double i = Astart; i <= Aend; i++)
                {
                    double degInRad = i * core::PI / 180.f;

                    cur.set(
                        cos(degInRad)*radius + center.X,
                        sin(degInRad)*radius + center.Y,
                        Zt
                    );
                    igs_transformation.transformVect(cur, cur);

                    data->Vertices.push_back({last.X, last.Y, last.Z, 0.f, 0.f, 0.f, e.irrColor, 0.f, (e.pattern)/6.f});
                    data->Vertices.push_back({cur.X,   cur.Y,  cur.Z, 0.f, 0.f, 0.f, e.irrColor, last.getDistanceFrom(cur), (e.pattern+1)/6.f});
                    data->Indices.push_back(data->Indices.size());
                    data->Indices.push_back(data->Indices.size());

                    last = cur;
                }
            }

            printf(
                "#100 Circular Arc (%f, %f, %f) to (%f, %f, %f) : center (%f, %f, %f)\n",
                start.X, start.Y, start.Z, end.X, end.Y, end.Z, center.X, center.Y, center.Z
            );
        }
        template<> //! composite curve
        void IgsBluidData<102>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * A composite curve is a continuous curve that results from the grouping of
             * certain individual constituent entities into a logical unit.
             * A composite curve can be defined as an ordered list of entities consisting
             * of point, connect point, and parameterized curv entities.
             * The list of entities appears in the parameter data entry
             */

//            float numberCurve(0);
//            s32 last = 0, cursor = 0;
//            readNextFloat(numberCurve, e, t[4], cursor, last, t);
//
//            for(int i = 0; i<numberCurve; ++i)
//            {
//            }

            printf("#102 Composite Curve : TODO\n");
        }
        template<> //! conic arc
        void IgsBluidData<104>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * A conic arc is a bounded connected portion of a conic curve that has distinct
             * start and end points. The parent conic curve can be an ellipse, a parabola
             * or a hyperbole. The definetion space coordinate system is always chosen so
             * that the conix arc lies in a plane either coincident with or parallel to the Xt, Yt plane.
             * Within such a plane, a conic is defined by the six coefficients in the following equation,
             * where Xt and Yt are the coordinates of a point in the Xt, Yt plane
             *
             * form(1) ellipse
             * form(2) hyperbola
             * form(3) parabola
             *
             * AX^2 + BXY + CY^2 + DX + EY +F = 0
             */

            // <<a direction can be associated with the arc>> ?

            /*
             * A parent conic curve is:
             *
             *      | A   B/2  D/2|        | A  B/2|
             * Q1 = |B/2   C   E/2|   Q2 = |D/2  C |   Q3 = A + C
             *      |D/2  E/2   F |
             *
             * if(Q2 > 0 && Q1*Q3 < 0) ellipse
             * if(Q2 < 0 && Q1 != 0)   hyperbola
             * if(Q2 == 0 && Q1 != 0)  parabola
             */

            float A, B, C, D, E, F;
            core::vector3df start, end;
            s32 last = 0, cursor = 0;

            readNextFloat(A, e, t[4], cursor, last, t);
            readNextFloat(B, e, t[4], cursor, last, t);
            readNextFloat(C, e, t[4], cursor, last, t);
            readNextFloat(D, e, t[4], cursor, last, t);
            readNextFloat(E, e, t[4], cursor, last, t);
            readNextFloat(F, e, t[4], cursor, last, t);

            readNextFloat(start.Z, e, t[4], cursor, last, t);
            end.Z = start.Z;

            readNextFloat(start.X, e, t[4], cursor, last, t);
            readNextFloat(start.Y, e, t[4], cursor, last, t);
            readNextFloat(end.X, e, t[4], cursor, last, t);
            readNextFloat(end.Y, e, t[4], cursor, last, t);

//            switch(e.form)
//            {
//                case 0: //! circle
//                    tmp.X = A*cos(theta);
//                    tmp.Y = A*cos(theta);
//                break;
//                case 1: //! ellipse
//                    tmp.X = A*cos(theta);
//                    tmp.Y = B*cos(theta);
//                break;
//                case 2: //! hyperbola
//                    tmp.X = A*sec(theta);
//                    tmp.Y = B*tan(theta);
//                break;
//                case 3: //! parabola
//                    tmp.X = A*t*t;
//                    tmp.Y = 2*A*t;
//                break;
//            }

            printf("#104 Conic Arc (%d) : Work-on\n", e.form);
        }
        template<> //! copious data
        void IgsBluidData<106>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * form(1) coordinate pairs
             * form(2) coordinate triples
             * form(2) coordinate x,y,z and i,j,k
             * form(11) 2D path
             * form(12) 3D path "Piecewise Linear Curve"
             * form(20) Centerline
             * form(21) Centerline through circle centers
             * form(31) Section lines - General use, iron, brick, stone masonry
             * form(32) Section lines - Steel
             * form(33) Section lines - Bronze, brass, copper
             * form(34) Section lines - Plastic, rubber
             * form(35) Section lines - fire brick, refractory material
             * form(36) Section lines - Marble, slate, glass
             * form(37) Section lines - Lead, zinc, magnesium, insulation
             * form(38) Section lines - Aluminum
             * form(40) "Witness Line"
             * form(63) closed 2D path
             */
            printf("#106 Copious Data (%d) : TODO\n", e.form);
        }
        template<> //! plane
        void IgsBluidData<108>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * the plane surface is defined by a point on the plane
             * and the normal direction to the surface
             *
             * form(0) : "Unbounded"
             * form(1) : "Bounded"
             */

            core::vector3df pos, nor;
            s32 last = 0, cursor = 0;

//            readNextFloat(pos.X, e, t[4], cursor, last, t);
//            readNextFloat(pos.Y, e, t[4], cursor, last, t);
//            readNextFloat(pos.Z, e, t[4], cursor, last, t);
//
//            readNextFloat(nor.X, e, t[4], cursor, last, t);
//            readNextFloat(nor.Y, e, t[4], cursor, last, t);
//            readNextFloat(nor.Z, e, t[4], cursor, last, t);
//
//            igs_transformation.transformVect(pos, pos);

            printf(
                "#108 Plane (%d) pos(%f, %f, %f) normal(%f, %f, %f) : TODO\n",
                e.form, pos.X, pos.Y, pos.Z, nor.X, nor.Y, nor.Z
            );

            //! TODO
        }
        template<> //! line
        void IgsBluidData<110>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * A line in IGES file is defined by its points
             * The coordinates of start and terminate point are
             * included in parameter data section of this entity
             */

            core::vector3df start, end;
            s32 last = 0, cursor = 0;

            readNextFloat(start.X, e, t[4], cursor, last, t);
            readNextFloat(start.Y, e, t[4], cursor, last, t);
            readNextFloat(start.Z, e, t[4], cursor, last, t);

            readNextFloat(end.X, e, t[4], cursor, last, t);
            readNextFloat(end.Y, e, t[4], cursor, last, t);
            readNextFloat(end.Z, e, t[4], cursor, last, t);

            igs_transformation.transformVect(start, start);
            igs_transformation.transformVect(end, end);

            printf(
                "#110 Line (%f, %f, %f) to (%f, %f, %f)\n",
                start.X, start.Y, start.Z, end.X, end.Y, end.Z
            );

            auto data = (scene::SMeshBuffer*)out->getMesh(IGS_LINE)->getMeshBuffer(
                out->getMesh(IGS_LINE)->getMeshBufferCount()-1
            );

            data->Vertices.push_back({start.X, start.Y, start.Z, 0.f, 0.f, 0.f, e.irrColor, 0.f, (e.pattern)/6.f});
            data->Vertices.push_back({end.X,   end.Y,   end.Z,   0.f, 0.f, 0.f, e.irrColor, start.getDistanceFrom(end), (e.pattern+1)/6.f});
            data->Indices.push_back(data->Indices.size());
            data->Indices.push_back(data->Indices.size());
        }
        template<> //! parametric spline curve
        void IgsBluidData<112>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * The parametric spline curve is a sequence of parametric polynomial segments.
             * The type of the curve is presented in the parameter data entry section
             */

            core::array<core::vector3df> pos;
//            float total = 0;
//
//            {
//                s32 last = 0, cursor = 0;
//
//                while(true)
//                {
//                    core::vector3df c;
//
//                    readNextFloat(c.X, e, t[4], cursor, last, t);
//                    if(cursor == e.parameter.size()) break;
//
//                    readNextFloat(c.Y, e, t[4], cursor, last, t);
//                    if(cursor == e.parameter.size()) break;
//
//                    readNextFloat(c.Z, e, t[4], cursor, last, t);
//
//                    pos.push_back(c);
//                }
//
//                if(pos.size() < 1)
//                    return;
//
                printf("#112 Parametric Spline Curve : %d points : TODO\n", pos.size());
//            }
//
//            auto data = (scene::SMeshBuffer*)out->getMesh(IGS_LINE)->getMeshBuffer(
//                out->getMesh(IGS_LINE)->getMeshBufferCount()-1
//            );

            //! TODO
        }
        template<> //! rational B-spline
        void IgsBluidData<126>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            /*
             * The rational B-Spline curve may represent analytic cuves.
             *
             * form(0) : ...
             * form(1) : Line
             * form(2) : Circular arc
             * form(3) : Elliptical arc
             * form(4) : Parabolic arc
             * form(5) : Hyperbolic arc
             */

//            core::array<core::vector3df> pos;
//            core::array<core::vector3df> control;
//
//            float n = 0;
//            float degree;
//
//            bool planar;
//            bool open;
//            bool rac;
//            bool periodic;
//
//            s32 last = 0, cursor = 0;
//            readNextFloat(n, e, t[4], cursor, last, t);
//            readNextFloat(degree, e, t[4], cursor, last, t);
//
//            readNextFloat(planar, e, t[4], cursor, last, t);
//            readNextFloat(open, e, t[4], cursor, last, t);
//            readNextFloat(rac, e, t[4], cursor, last, t);
//            readNextFloat(periodic, e, t[4], cursor, last, t);

            printf("#126 parametric b-spline (%d) : %d points\n", e.form, (int)n);

//            for(float i = 0; i<n ; ++i)
//            {
//                core::vector3df c;
//
//                readNextFloat(c.X, e, t[4], cursor, last, t);
//                readNextFloat(c.Y, e, t[4], cursor, last, t);
//                readNextFloat(c.Z, e, t[4], cursor, last, t);
//
//                printf("    point (%f, %f, %f)\n", c.X, c.Y , c.Z);
//
//                pos.push_back(c);
//            }

            //! TODO
        }
        template<> //! Offset Curve
        void IgsBluidData<130>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#130 Offset Curve\n");
        }
        template<> //! Boundary
        void IgsBluidData<141>(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            printf("#141 Boundary\n");
        }
    }
}
