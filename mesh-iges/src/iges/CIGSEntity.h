#ifndef __igs_ENTITY_H__
#define __igs_ENTITY_H__

#include <irrString.h>
#include <vector2d.h>
#include <SColor.h>

namespace irr
{
    namespace scene
    {
        enum LINE_FONT_PATTERN
        {
            LFP_DEFAULT,
            LFP_SOLID,
            LFP_DASHED,
            LFP_PHANTOM,
            LFP_CENTERLINE,
            LFP_DOTTED,
            LFP_COUNT,
        };

        class IgsEntity
        {
            public:
                void updateIrrInfo();
            public:
                int type;
                int sequence;
                int pointer;

                int color;
                int entity;
                int form;
                int label;
                int level;
                int lines;
                int pattern;
                int structure;
                int transform;
                int view;
                int weight;

                core::stringc subs;
                core::stringc status;
                core::stringc parameter;
            public:
                video::SColor irrColor;
        };
    }
}

#endif // __C_igs_ENTITY_H__
