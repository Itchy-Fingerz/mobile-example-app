// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

//#include "GlobeCameraExampleBase.h"
#include "Modules.h"
#include "Rendering.h"
#include "ITextureFileLoader.h"
#include "GLHelpers.h"
#include "IRenderableFilter.h"
#include "Bounds.h"
#include "GlobeCameraController.h"

namespace ExampleApp
{
    namespace BillboardedSprite
    {
        class BillboardedSpriteExample : public Eegeo::Rendering::IRenderableFilter //public GlobeCameraExampleBase,
        {
        private:
            Eegeo::Modules::Core::RenderingModule& m_renderingModule;
            Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
            
            Eegeo::Rendering::Renderables::BatchedSpriteRenderable* m_pBatchedSpriteRenderable;
            Eegeo::Rendering::Shaders::BatchedSpriteShader* m_pBatchedSpriteShader;
            Eegeo::Rendering::Materials::BatchedSpriteMaterial* m_pBatchedSpriteMaterial;
            Eegeo::Rendering::Materials::BatchedSpriteMaterial* m_pAsyncBatchedSpriteMaterial;
            
            Eegeo::Helpers::GLHelpers::TextureInfo m_textureInfo;
            Eegeo::Helpers::GLHelpers::TextureInfo m_asyncTextureInfo;
        
            Eegeo::dv3 m_spriteEcefPosition;
            Eegeo::v2 m_spriteDimensions;
            Eegeo::Geometry::Bounds2D m_spriteUvBounds;
            Eegeo::v4 m_spriteColor;
            
            Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

        public:
            BillboardedSpriteExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& pCameraController,
                                 Eegeo::Modules::Core::RenderingModule& renderingModule,
                                 Eegeo::Helpers::ITextureFileLoader& textureFileLoader);
            
            ~BillboardedSpriteExample();

            static std::string GetName()
            {
                return "BillboardedSpriteExample";
            }
            std::string Name() const
            {
                return GetName();
            }

            void Start(Eegeo::dv3 spritePosition);
            void Destroy();
            
            void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        };
    }
}


