#include "BillboardedSpriteExample.h"

#include "BatchedSpriteRenderable.h"
#include "BatchedSpriteShader.h"
#include "BatchedSpriteMaterial.h"

#include "RenderingModule.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"
#include "RenderableFilters.h"
#include "RenderQueue.h"
#include "RenderContext.h"

#include "LatLongAltitude.h"
#include "GlobeCameraController.h"
#include "CameraHelpers.h"

#include <string>

namespace ExampleApp
{
    namespace
    {
        const Eegeo::Space::LatLongAltitude SanFranBayLatLong = Eegeo::Space::LatLongAltitude::FromDegrees(26.155105, -78.792659, 0.0);
    }
    
    namespace BillboardedSprite
    {
        //                                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
        BillboardedSpriteExample::BillboardedSpriteExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
                                                           Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                           Eegeo::Helpers::ITextureFileLoader& textureFileLoader)
        : m_globeCameraController(cameraController)
        //, m_globeCameraTouchController(cameraTouchController)
        , m_renderingModule(renderingModule)
        , m_textureFileLoader(textureFileLoader)
        , m_pBatchedSpriteRenderable(NULL)
        , m_pBatchedSpriteShader(NULL)
        , m_pBatchedSpriteMaterial(NULL)
        , m_pAsyncBatchedSpriteMaterial(NULL)
        , m_spriteEcefPosition(SanFranBayLatLong.ToECEF())
        , m_spriteDimensions(Eegeo::v2(30.0, 30.0))
        , m_spriteUvBounds(Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()))
        , m_spriteColor(Eegeo::v4::One())
        {
            m_textureInfo.textureId = 0;
            m_textureInfo.height = 0;
            m_textureInfo.width = 0;
            
            m_asyncTextureInfo.textureId = 0;
            m_asyncTextureInfo.height = 0;
            m_asyncTextureInfo.width = 0;
        }
        
        BillboardedSpriteExample::~BillboardedSpriteExample()
        {
            Destroy();
        }
        
        void BillboardedSpriteExample::Start(Eegeo::dv3 spritePosition)
        {
            Destroy();
            m_spriteEcefPosition = spritePosition;
            Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = m_renderingModule.GetShaderIdGenerator();
            m_pBatchedSpriteShader = Eegeo::Rendering::Shaders::BatchedSpriteShader::Create(shaderIdGenerator.GetNextId());
            
            std::string localTextureFile = "you_are_here_callout.png";

            bool success = m_textureFileLoader.LoadTexture(m_textureInfo, localTextureFile, false);
            Eegeo_ASSERT(success, "failed to load texture");

            Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = m_renderingModule.GetMaterialIdGenerator();
            m_pBatchedSpriteMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::BatchedSpriteMaterial)(materialIdGenerator.GetNextId(),
                                                                                                    "ExampleBatchedSpriteMaterial",
                                                                                                    *m_pBatchedSpriteShader,
                                                                                                    m_textureInfo.textureId);
            
            Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool = m_renderingModule.GetVertexLayoutPool();
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = m_renderingModule.GetVertexBindingPool();

            const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(vertexLayoutPool.GetForTexturedColoredVertex(),
                                                                                                                     m_pBatchedSpriteShader->GetVertexAttributes());
            
            m_pBatchedSpriteRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::BatchedSpriteRenderable)(Eegeo::Rendering::LayerIds::InteriorEntities,
                                                                                                           m_pBatchedSpriteMaterial,
                                                                                                           vertexBinding,
                                                                                                           m_renderingModule.GetGlBufferPool(),
                                                                                                           Eegeo::Rendering::Renderables::BatchedSpriteAnchor::Centre);
            
            Eegeo::Rendering::RenderableFilters& renderableFilters = m_renderingModule.GetRenderableFilters();
            renderableFilters.AddRenderableFilter(*this);
            
            Eegeo::Space::EcefTangentBasis cameraInterestBasis;
            Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_spriteEcefPosition,
                                                                              0.0,
                                                                              cameraInterestBasis);
            m_globeCameraController.SetView(cameraInterestBasis, 1000.f);
        }
        
        void BillboardedSpriteExample::Destroy()
        {
            
            
            if (m_pBatchedSpriteRenderable != NULL)
            {
                Eegeo::Rendering::RenderableFilters& renderableFilters = m_renderingModule.GetRenderableFilters();
                renderableFilters.RemoveRenderableFilter(*this);
                
                Eegeo_DELETE m_pBatchedSpriteRenderable;
                Eegeo_DELETE m_pBatchedSpriteMaterial;
                Eegeo_DELETE m_pAsyncBatchedSpriteMaterial;
                Eegeo_DELETE m_pBatchedSpriteShader;
                Eegeo_GL(glDeleteTextures(1, &m_textureInfo.textureId));
                Eegeo_GL(glDeleteTextures(1, &m_asyncTextureInfo.textureId));
            }

        }

        void BillboardedSpriteExample::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
        {
            m_pBatchedSpriteRenderable->Reset();
            const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
            m_pBatchedSpriteRenderable->SetModelViewProjection(renderCamera.GetViewProjectionMatrix());
            
            m_pBatchedSpriteRenderable->AddSprite(renderCamera, m_spriteEcefPosition, m_spriteUvBounds.min, m_spriteUvBounds.max, m_spriteColor, m_spriteDimensions);
            renderQueue.EnqueueRenderable(*m_pBatchedSpriteRenderable);
        }
    }
}
