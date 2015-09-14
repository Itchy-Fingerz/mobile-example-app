// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "GLHelpers.h"
#include <string>
#include <vector>

namespace ExampleApp
{
    namespace Materials
    {
        struct CubeFaceFileNames
        {
            std::string positiveXFileName;
            std::string negativeXFileName;
            std::string positiveYFileName;
            std::string negativeYFileName;
            std::string positiveZFileName;
            std::string negativeZFileName;
        };
        
        class ICubeTextureFileLoader
        {
        public:
            virtual ~ICubeTextureFileLoader() { }
            
            virtual bool LoadPNGCube(Eegeo::Helpers::GLHelpers::TextureInfo& textureInfo, const CubeFaceFileNames& cubeFaceFileNames, bool invertVertically) = 0;
        };
    }
}
