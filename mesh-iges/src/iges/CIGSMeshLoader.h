#ifndef __I_igs_MESH_LOADER_H_INCLUDED__
#define __I_igs_MESH_LOADER_H_INCLUDED__

#include "CIGSEntity.h"

#include <IMeshLoader.h>
#include <EPrimitiveTypes.h>
#include <irrArray.h>
#include <vector3d.h>
#include <matrix4.h>

namespace irr
{
    namespace io
    {
        class IReadFile;
    }
    namespace scene
    {
        class IAnimatedMesh;
        class SAnimatedMesh;

        enum E_IGS_PRIMITIVE_TYPE
        {
            IGS_POINT,
            IGS_LINE,
            IGS_SURFACE,
            IGS_TEXT,
            IGS_COUNT
        };

        static const E_PRIMITIVE_TYPE igs_render_mesh_buffer[] =
        {
            EPT_POINT_SPRITES,
            EPT_LINES,
            EPT_TRIANGLES,
            EPT_TRIANGLES // this is for text rendering
        };

        static const char* igs_global_information_label_table[] =
        {
            "Parameter Delimiter Character",
            "Record Delimiter Character",
            "Product ID from Sender",
            "File Name",
            "System ID",
            "Pre-processor Version",
            "Number of Bits for Integers",
            "Single Precision Magnitude",
            "Single Precision Significance",
            "Double Precision Magnitude",
            "Double Precision Significance",
            "Product ID for Receiver",
            "Model Space Scale",
            "Unit Flag",
            "Units",
            "Maximum Number of Line Weights",
            "Size of Maximum Line Width",
            "Date & Time Stamp",
            "Minimum User-intended Resolution",
            "Approximate Maximum Coordinate",
            "Name of Author",
            "Author's Organization",
            "IGES Version Number",
            "Drafting Standard Code",
            0
        };

        static core::matrix4 igs_transformation;

        class CIGSMeshLoader : public IMeshLoader
        {
            public:
                CIGSMeshLoader() noexcept;

                virtual ~CIGSMeshLoader() noexcept;

                virtual bool isALoadableFileExtension(const io::path& filename) const noexcept;

                virtual IAnimatedMesh* createMesh(io::IReadFile* file) noexcept;

                virtual const core::array<core::stringc>& getLastLoadedGlobalInformation() const noexcept;

                virtual core::array<IgsEntity>& getLastLoadedEntitiesList() noexcept;

                void computeEntity(IAnimatedMesh*, core::array<IgsEntity>&) const noexcept;
            private:
                // split @info into array of string store to @
                void computeGlobalInfo(core::stringc&) noexcept;
            private:
                char t[7];
                core::array<IgsEntity> list;
                core::array<core::stringc> info;
                char separator;
                char record;
        };
    }
}

#endif
