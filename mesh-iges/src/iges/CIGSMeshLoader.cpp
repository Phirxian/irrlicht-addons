#include "CIGSMeshLoader.h"
#include "CIGSType.h"

#include <fast_atof.h>
#include <IReadFile.h>
#include <SAnimatedMesh.h>
#include <SMeshBuffer.h>
#include <SMesh.h>

#ifdef _DEBUG
#include <iostream>
#endif

namespace irr
{
    namespace scene
    {
        CIGSMeshLoader::CIGSMeshLoader() noexcept
            : t{' ', '\t', '\n', '\r', 0, 0, 0}
        {
        }
        CIGSMeshLoader::~CIGSMeshLoader() noexcept
        {
        }
        bool CIGSMeshLoader::isALoadableFileExtension(const io::path& filename) const noexcept
        {
            return core::hasFileExtension(filename, "iges") ||
                   core::hasFileExtension(filename, "igs");
        }
        core::array<IgsEntity>& CIGSMeshLoader::getLastLoadedEntitiesList() noexcept
        {
            return list;
        }
        const irr::core::array<irr::core::stringc>& CIGSMeshLoader::getLastLoadedGlobalInformation() const noexcept
        {
            return info;
        }
        IAnimatedMesh* CIGSMeshLoader::createMesh(io::IReadFile* file) noexcept
        {
            igs_transformation = core::IdentityMatrix;

            irr::core::stringc buffer;

            buffer.reserve(81);
            // force overriding used variable on buffer
            for(int i = 0; i<81; ++i)
                buffer += " ";

            file->read(const_cast<char*>(buffer.c_str()), 81);

            #ifdef _DEBUG
                std::cout << buffer;
            #endif

            if(buffer[72] != 'S')
                return nullptr;

            irr::core::stringc info;
            irr::core::stringc comment =
                buffer.subString(0, 71).trim();
            irr::core::stringc tmp;

            bool first_line = true;
            int  index = 0;
            int  ptr;
            int  type;

            int terminated[5] = {0, 0, 0, 0, 0};

            irr::scene::SAnimatedMesh *result = new irr::scene::SAnimatedMesh();
            for(int i = 0; i<IGS_COUNT; ++i)
            {
                irr::scene::SMeshBuffer *buff = new irr::scene::SMeshBuffer();
                irr::scene::SMesh *data = new irr::scene::SMesh();
                data->addMeshBuffer(buff);
                result->addMesh(data);
                data->drop();
                buff->drop();
            }

            list.clear();
            IgsEntity e;

            while(file->read(const_cast<char*>(buffer.c_str()), 81))
            {
                #ifdef _DEBUG
                    std::cout << buffer;
                #endif

                switch(buffer[72])
                {
                    case 'G':
                        if(info.empty())
                        {
                            int offset = 0;

                            if(buffer[0] == '1' && buffer[1] == 'H')
                            {
                                separator = buffer[2];
                                offset = buffer.findNext(separator, 4)-1;
                                record = offset ? buffer[offset] : ';';
                            }
                            else
                            {
                                separator = ',';
                                offset = buffer.findNext(separator, 1)-1;
                                record = offset ? buffer[offset] : ';';
                            }
                        }
                        info += buffer.subString(0, 72).trim();
                    break;
                    case 'D':
                        if(first_line)
                        {
                            e.type      = readInt(buffer,  0, 9);
                            e.pointer   = readInt(buffer,  9, 8);
                            e.structure = readInt(buffer, 17, 8);
                            e.pattern   = readInt(buffer, 25, 8);
                            e.level     = readInt(buffer, 33, 8);
                            e.view      = readInt(buffer, 41, 8);
                            e.transform = readInt(buffer, 49, 8);
                            e.label     = readInt(buffer, 57, 8);
                            e.status    = buffer.subString(66, 8).trim();
                            e.sequence  = readInt(buffer, 73, 8);
                            e.parameter = "";
                            first_line = false;
                        }
                        else
                        {
                            e.weight = readInt(buffer,  9, 8);
                            e.color  = readInt(buffer, 17, 8);
                            e.lines  = readInt(buffer, 25, 8);
                            e.form   = readInt(buffer, 33, 8);
                            e.entity = readInt(buffer, 57, 8);
                            e.subs   = buffer.subString(66, 8).trim();

                            list.push_back(e);
                            first_line = true;
                        }
                    break;
                    case 'P':

                        if(first_line)
                        {
                            type = readInt(buffer,  0, 9);
                            tmp = buffer.subString(4, 60).trim();
                            ptr = readInt(buffer, 73, 8);
                            first_line = false;
                        }
                        else tmp += buffer.subString(0, 64).trim();

                        tmp = tmp;

                        if(tmp.size() > 0 && tmp[tmp.size()-1] == record)
                        {
                            bool found = false;

                            for(int i = 0; i<list.size(); ++i)
                            {
                                IgsEntity &e = list[i];
                                if(e.pointer == ptr && e.type == type)
                                {
                                    found = true;
                                    first_line = true;
                                    e.parameter = tmp;
                                    break;
                                }
                            }

                            if(!found)
                                printf("unresolved parameter (%d)::%s\n", ptr, tmp.c_str());

                            first_line = true;
                        }

                        terminated[5]++;
                    break;
                    case 'S':
                        comment += "\n";
                        comment += buffer.subString(0, 71).trim();
                    break;
                    case 'T':
                        terminated[0] = readInt(buffer,  1, 7);
                        terminated[1] = readInt(buffer,  9, 7);
                        terminated[2] = readInt(buffer, 17, 7);
                        terminated[3] = readInt(buffer, 25, 7);
                    break;
                    default:
                        // nothing
                    break;
                }
            }

            printf("\n");

            if(comment.size())
            {
                printf(
                    "\n************  Comments  Section  *************\n\n%s\n",
                    comment.c_str()
                );
            }

            t[4] = separator;
            t[5] = record;
            computeGlobalInfo(info);

            #ifdef _DEBUG
                std::cout << "\n************  Terminate Section  *************\n\n"
                          << terminated[0] << " records in Start Section\n"
                          << terminated[1] << " records in Global Section\n"
                          << terminated[2] << " records in Directory Entry Section (" << terminated[3] << " entities)\n"
                          << terminated[5] << " records in Parameter Data Section"
                          << std::endl;
            #endif

            computeEntity(result, list);

            for(int i = 0; i<IGS_COUNT; ++i)
            {
                auto data = (irr::scene::SMesh*)result->getMesh(i);
                for(int j = 0; j<data->getMeshBufferCount(); ++j)
                    data->getMeshBuffer(j)->recalculateBoundingBox();
                data->recalculateBoundingBox();
            }

            result->recalculateBoundingBox();
            return result;
        }
        void CIGSMeshLoader::computeEntity(IAnimatedMesh *out, irr::core::array<IgsEntity> &entity) const noexcept
        {
            printf(
                "\n**************  Entity Section  **************\n\n"
                "-------------------\n"
            );

            //! sort entity by color then by level ?
            //! may improve reuse ?

            for(int i = 0; i<entity.size(); ++i)
            {
                IgsEntity &e = entity[i];
                e.updateIrrInfo();

                #ifdef _DEBUG
                    std::cout << "type: "      << e.type      << '\n'
                              << "pointer: "   << e.pointer   << '\n'
                              << "sequence: "  << e.sequence  << '\n'

                              << "color: "     << e.color     << '\n'
                              << "form: "      << e.form      << '\n'
                              << "label: "     << e.label     << '\n'
                              << "level: "     << e.level     << '\n'
                              << "lines: "     << e.lines     << '\n'
                              << "pattern: "   << e.pattern   << '\n'
                              << "structure: " << e.structure << '\n'
                              << "transform: " << e.transform << '\n'
                              << "view: "      << e.view      << '\n'
                              << "weight: "    << e.weight    << '\n'

                              << "subs: "      << e.subs.c_str()      << '\n'
                              << "status: "    << e.status.c_str()    << '\n'
                              << "parameter: " << e.parameter.c_str() << '\n'

                              << "-------------------" << std::endl;
                #endif

                IgsAutoBuildData::apply(const_cast<CIGSMeshLoader*>(this), out, e, t);
            }

            printf("\n***********************************************\n");
        }
        void CIGSMeshLoader::computeGlobalInfo(core::stringc &data) noexcept
        {
            u32 lastpos = 0;
            u32 i = 0;

            for(; i<data.size(); ++i)
            {
                if(data[i] == separator)
                {
                    int H = data.findNext('H', lastpos+1);
                        H = H > lastpos+2 ? 0 : H;

                    if(H > 0)
                    {
                        int length = readInt(data, lastpos, H-lastpos);
                        info.push_back(core::stringc(&data[H+1], length).trim());
                        lastpos = H+length+2;
                        i = lastpos;
                    }
                    else
                    {
                        info.push_back(core::stringc(&data[lastpos], i - lastpos).trim());
                        lastpos = i + 1;
                    }
                }
            }

            if((data.size() - 1) > lastpos)
                info.push_back(core::stringc(&data[lastpos], (data.size() - 1) - lastpos));

            if(info[0].empty())
                info[0] = "using default ','";

            if(info[1].empty())
                info[1] = "using default ';'";

            printf("\n**************  Global Section  **************\n\n");

            for(int i = 0; i< info.size(); ++i)
                printf("%s: %s\n", igs_global_information_label_table[i], info[i].c_str());
        }
    }
}
