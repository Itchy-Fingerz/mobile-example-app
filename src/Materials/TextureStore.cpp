// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TextureStore.h"
#include "ICubeTextureFileLoader.h"
#include "ITextureFileLoader.h"
#include <vector>

namespace ExampleApp
{
    namespace Materials
    {
        TextureStore::TextureStore(ICubeTextureFileLoader& cubeTextureFileLoader,
                                   Eegeo::Helpers::ITextureFileLoader& textureFileLoader)
        : m_cubeTextureFileLoader(cubeTextureFileLoader)
        , m_textureFileLoader(textureFileLoader)
        {
            m_chromeTextureInfo.textureId = 0;
            m_chromeTextureInfo.width = 0;
            m_chromeTextureInfo.height = 0;
            
            m_glassTextureInfo.textureId = 0;
            m_glassTextureInfo.width = 0;
            m_glassTextureInfo.height = 0;
            
            m_floorTextureInfo.textureId = 0;
            m_floorTextureInfo.width = 0;
            m_floorTextureInfo.height = 0;
            
            m_lightCubeTextureInfo.textureId = 0;
            m_lightCubeTextureInfo.width = 0;
            m_lightCubeTextureInfo.height = 0;
            
            const std::string chromeTextureFileName = "Materials/ChromeTexture.png";
            const std::string glassTextureFileName = "Materials/GlassReflection.png";
            const std::string floorTextureFileName = "Materials/FloorTiles2x2.png";
            
            const bool generateMipmaps = true;
            
            bool success = m_textureFileLoader.LoadTexture(m_chromeTextureInfo, chromeTextureFileName, generateMipmaps);
            Eegeo_ASSERT(success, "failed to load chrome texture");
            
            success = m_textureFileLoader.LoadTexture(m_glassTextureInfo, glassTextureFileName, generateMipmaps);
            Eegeo_ASSERT(success, "failed to load glass texture");
            
            success = m_textureFileLoader.LoadTexture(m_floorTextureInfo, floorTextureFileName, generateMipmaps);
            Eegeo_ASSERT(success, "failed to load floor texture");
            
            success = LoadLightCubeMap();
            Eegeo_ASSERT(success, "failed to load lighting cube texture");
        }
        
        TextureStore::~TextureStore()
        {
            if (m_chromeTextureInfo.textureId != 0)
            {
                Eegeo_GL(glDeleteTextures(1, &m_chromeTextureInfo.textureId));
            }
            
            if(m_glassTextureInfo.textureId != 0)
            {
                Eegeo_GL(glDeleteTextures(1, &m_glassTextureInfo.textureId));
            }
            
            if(m_floorTextureInfo.textureId != 0)
            {
                Eegeo_GL(glDeleteTextures(1, &m_floorTextureInfo.textureId));
            }
            
            if(m_lightCubeTextureInfo.textureId != 0)
            {
                Eegeo_GL(glDeleteTextures(1, &m_lightCubeTextureInfo.textureId));
            }
        }
        
        GLuint TextureStore::GetChromeTextureID() const
        {
            return m_chromeTextureInfo.textureId;
        }
        
        GLuint TextureStore::GetGlassTextureID() const
        {
            return m_glassTextureInfo.textureId;
        }
        
        GLuint TextureStore::GetLightCubeTextureID() const
        {
            return m_lightCubeTextureInfo.textureId;
        }
        
        GLuint TextureStore::GetFloorTextureID() const
        {
            return m_floorTextureInfo.textureId;
        }
        
        bool TextureStore::LoadLightCubeMap()
        {
            const std::string rightFaceFileName = "Materials/PointLightCube_Right.png";
            const std::string leftFaceFileName = "Materials/PointLightCube_Left.png";
            const std::string topFaceFileName = "Materials/PointLightCube_Top.png";
            const std::string bottomFaceFileName = "Materials/PointLightCube_Bottom.png";
            const std::string frontFaceFileName = "Materials/PointLightCube_Front.png";
            const std::string backFaceFileName = "Materials/PointLightCube_Back.png";
            
            CubeFaceFileNames cubeFaceFileNames;
            cubeFaceFileNames.positiveXFileName = rightFaceFileName;
            cubeFaceFileNames.negativeXFileName = leftFaceFileName;
            cubeFaceFileNames.positiveYFileName = topFaceFileName;
            cubeFaceFileNames.negativeYFileName = bottomFaceFileName;
            cubeFaceFileNames.positiveZFileName = frontFaceFileName;
            cubeFaceFileNames.negativeZFileName = backFaceFileName;
            
            return m_cubeTextureFileLoader.LoadPNGCube(m_lightCubeTextureInfo, cubeFaceFileNames, false);
        }
    }
}