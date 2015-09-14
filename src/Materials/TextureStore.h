// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "GLHelpers.h"
#include "MaterialsIncludes.h"
#include "Helpers.h"
#include <string>

namespace ExampleApp
{
    namespace Materials
    {
        class TextureStore : protected Eegeo::NonCopyable
        {
        public:
            TextureStore(ICubeTextureFileLoader& cubeTextureFileLoader,
                         Eegeo::Helpers::ITextureFileLoader& textureFileLoader);
            
            ~TextureStore();
            
            GLuint GetChromeTextureID() const;
            GLuint GetGlassTextureID() const;
            GLuint GetLightCubeTextureID() const;
            GLuint GetFloorTextureID() const;
            
        private:
            bool LoadLightCubeMap();
            
            ICubeTextureFileLoader& m_cubeTextureFileLoader;
            Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
            
            Eegeo::Helpers::GLHelpers::TextureInfo m_chromeTextureInfo;
            Eegeo::Helpers::GLHelpers::TextureInfo m_glassTextureInfo;
            Eegeo::Helpers::GLHelpers::TextureInfo m_lightCubeTextureInfo;
            Eegeo::Helpers::GLHelpers::TextureInfo m_floorTextureInfo;
        };
    }
}