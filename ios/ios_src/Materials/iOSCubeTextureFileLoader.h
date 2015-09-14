// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICubeTextureFileLoader.h"
#include "IJpegLoader.h"
#include "Types.h"
#include "MacTypes.h"
#include "GLHelpers.h"
#include <string>
#include <vector>

namespace Eegeo
{
    namespace iOS
    {
        class iOSFileIO;
    }
}

namespace ExampleApp
{
    namespace Materials
    {
        namespace iOS
        {
            class iOSCubeTextureFileLoader : public ICubeTextureFileLoader, protected Eegeo::NonCopyable
            {
                Eegeo::iOS::iOSFileIO& m_fileIO;
            public:
                iOSCubeTextureFileLoader(Eegeo::iOS::iOSFileIO& fileIO);
                ~iOSCubeTextureFileLoader();
                
                bool LoadPNGCube(Eegeo::Helpers::GLHelpers::TextureInfo& textureInfo, const CubeFaceFileNames& cubeFaceFileNames, bool invertVertically);
            };
        }
    }
}
