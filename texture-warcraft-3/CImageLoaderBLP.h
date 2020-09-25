#ifndef __C_BLP_IMAGE_LOADER_H_INCLUDED__
#define __C_BLP_IMAGE_LOADER_H_INCLUDED__

/**
* Copyright (C) <2014> <Jehan-antoine vayssade>
* Ovan/Magun contact on irrlicht-fr.org or ovan@sleek-think.ovh
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#include "IrrCompileConfig.h"
#define _IRR_COMPILE_WITH_BLP_LOADER_

// force plugin compilation
// guard efined if loader included to the engine
#ifdef _IRR_COMPILE_WITH_BLP_LOADER_

#include <IImageLoader.h>

namespace irr
{
    namespace video
    {
        struct sharedheader;
        class IVideoDriver;
        class CImageLoaderBLP : public IImageLoader
        {
            protected:
                enum Compression : int
                {
                    JPG = 0,
                    BLP = 1,
                    RAW = 2,
                    DXT = 3
                };
            public:
                CImageLoaderBLP(IVideoDriver*);
                virtual ~CImageLoaderBLP();

                virtual bool isALoadableFileExtension(const io::path& filename) const;
                virtual bool isALoadableFileFormat(io::IReadFile* file) const;
                virtual IImage* loadImage(io::IReadFile* file) const;
            protected:
                IImage* decompressBLP(const sharedheader&, char *, size_t) const;
                IImage* decompressDXT(const sharedheader&, char *, size_t) const;
                IImage* decompressRaw(const sharedheader&, char *, size_t) const;
                IImage* decompressJpg(const sharedheader&, char *, size_t) const;
            private:
                IVideoDriver *driver;
        };

        IImageLoader* createImageLoaderBLP();
    }
}

#endif
#endif
