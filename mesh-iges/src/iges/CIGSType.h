#ifndef __igs_TYPE_IMP_HEADER__
#define __igs_TYPE_IMP_HEADER__

#include <fast_atof.h>
#include <SAnimatedMesh.h>
#include <SMeshBuffer.h>
#include <SMesh.h>

namespace irr
{
    namespace scene
    {
        #define readNextFloat(out, e, separator, cursor, last, t) \
        {\
            int tmp = e.parameter.findNext(separator, cursor+1); \
            cursor = tmp < 0 ? e.parameter.size() : tmp; \
            out = irr::core::fast_atof(e.parameter.subString(last, cursor-last).trim(t).c_str()); \
            last = cursor; \
        }

        #define readInt(buffer, start, length)\
            irr::core::strtol10(buffer.subString(start, length).trim().c_str())

        inline s32 clamp(s32 idx, s32 size)
        {
            return ( idx<0 ? size+idx : ( idx>=size ? idx-size : idx ) );
        }

        template<int type>
        inline void IgsBluidData(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
        {
            //! empty section
        }

        template<int from, int to, int inc>
        struct IgsAutoUnrollBluidData
        {
            static inline void apply(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
            {
                IgsAutoUnrollBluidData<from    , from, inc>::apply(loader, out, e, t);
                IgsAutoUnrollBluidData<from+inc, to  , inc>::apply(loader, out, e, t);
            }
        };

        // terminal case
        template<int end, int incr>
        struct IgsAutoUnrollBluidData<end, end, incr>
        {
            static inline void apply(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
            {
                if(e.type == end)
                    IgsBluidData<end>(loader, out, e, t);
            }
        };

        struct IgsAutoBuildData
        {
            static inline void apply(CIGSMeshLoader *loader, IAnimatedMesh *out, const IgsEntity &e, const char t[7]) noexcept
            {
                /*
                 * Implemented feature:
                 *   -100 circular arc
                 *   -110 line
                 *   -116 point
                 *   -124 transformation matrix
                 * Working on:
                 *   -112 parametric spline curve
                 *   -123 direction
                 *   -126 rational B-spline
                 *   -190 plane
                 *   -502 vertex
                 *   -504 edged
                 *   -508 loop
                 *   -510 face
                 * No yet:
                 *   -202 annotation
                 *   -212 text
                 *   -all other
                 */

                /*
                 * Annotation entities:
                 *   -202 Angular dimension entity
                 *   -106 Centerline entity
                 *   -206 Diameter dimension entity
                 *   -208 Flag note entity
                 *   -210 General label entity
                 *   -212 General note entity
                 *   -214 Leader (arrow) entity
                 *   -216 Linear dimension entity
                 *   -218 Ordinate dimension entity
                 *   -220 Point dimension entity
                 *   -222 Radius dimension entity
                 *   -106 Section entity
                 *   -106 Witness line entity
                 * may need to disable annotation entites (CIGSMeshLoader property)
                 */

                IgsAutoUnrollBluidData<000, 000, 0>::apply(loader, out, e, t);
                IgsAutoUnrollBluidData<100, 500, 2>::apply(loader, out, e, t);
                IgsAutoUnrollBluidData<123, 123, 0>::apply(loader, out, e, t);
                IgsAutoUnrollBluidData<141, 141, 0>::apply(loader, out, e, t);
                IgsAutoUnrollBluidData<143, 143, 0>::apply(loader, out, e, t);
                IgsAutoUnrollBluidData<700, 998, 2>::apply(loader, out, e, t);
            }
        };
    }
}


#endif
