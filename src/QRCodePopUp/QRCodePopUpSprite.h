// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Modules.h"
#include "Rendering.h"
#include "ITextureFileLoader.h"
#include "GLHelpers.h"
#include "IRenderableFilter.h"
#include "Bounds.h"
#include "GlobeCameraController.h"
#include "AppInterface.h"

namespace ExampleApp
{
    namespace QRCodePopUp
    {
        class QRCodePopUpSprite : public Eegeo::Rendering::IRenderableFilter
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
            bool m_isSpriteAdded;

        public:
            QRCodePopUpSprite(Eegeo::Camera::GlobeCamera::GlobeCameraController& pCameraController,
                                 Eegeo::Modules::Core::RenderingModule& renderingModule,
                                 Eegeo::Helpers::ITextureFileLoader& textureFileLoader);
            
            ~QRCodePopUpSprite();
            
            void OnSingleTap(const AppInterface::TapData& data);

            void Show(Eegeo::dv3 spritePosition);
            void Remove();
            
            void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        };
    }
}


