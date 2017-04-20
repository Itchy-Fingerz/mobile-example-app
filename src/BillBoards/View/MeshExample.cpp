// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MeshExample.h"
#include "BillBoardsMeshRenderable.h"
#include "BillBoardsMeshUnlitTexturedMaterial.h"
#include "GeometryHelpers.h"

#include "RenderingModule.h"
#include "ITextureFileLoader.h"
#include "GlobeCameraController.h"
#include "VertexLayoutPool.h"
#include "VertexLayout.h"
#include "VertexLayoutElement.h"
#include "Mesh.h"
#include "LayerIds.h"
#include "TexturedUniformColoredShader.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "Colors.h"

#include "VertexBindingPool.h"
#include "LatLongAltitude.h"
#include "CoordinateConversion.h"
#include "RenderQueue.h"
#include "RenderableFilters.h"
#include "EnvironmentFlatteningService.h"
#include "CameraHelpers.h"
#include "RenderContext.h"
#include "RenderCamera.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "InteriorsModel.h"
#include "InteriorHeightHelpers.h"
#include "EnvironmentRayCaster.h"
#include "IntersectionTests.h"

#include <algorithm>
#include <cmath>

namespace ExampleApp
{
    
    namespace BillBoards
    {
        namespace View
        {
            namespace
            {
                struct PositionUvVertex
                {
                    float x;
                    float y;
                    float z;
                    float u;
                    float v;
                };
                
                inline PositionUvVertex MakePositionUvVertex(const Eegeo::v3& pos, const Eegeo::v2& uv)
                {
                    PositionUvVertex v;
                    v.x = pos.x;
                    v.y = pos.y;
                    v.z = pos.z;
                    v.u = uv.x;
                    v.v = uv.y;
                    return v;
                }
                
                inline PositionUvVertex GeometryHelpersVertexToPositionUvVertex(const Vertex& v)
                {
                    return MakePositionUvVertex(v.position, v.uv);
                }
                
                Eegeo::Rendering::VertexLayouts::VertexLayout* CreatePositionUvVertexLayout()
                {
                    using namespace Eegeo::Rendering::VertexLayouts;
                    VertexLayout* pLayout = new (VertexLayout)(sizeof(PositionUvVertex));
                    
                    int positionOffset = offsetof(PositionUvVertex, x);
                    pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::Position, 3, GL_FLOAT,  positionOffset));
                    
                    int uvOffset = offsetof(PositionUvVertex, u);
                    pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::UV, 2, GL_FLOAT, uvOffset));
                    
                    return pLayout;
                }
                
                Eegeo::Rendering::Mesh* CreateUnlitBoxMesh(float width, float height, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
                {
                    Eegeo::v3 halfDimensions(width/2, height, width/2);
                    std::vector<Vertex> boxVertices;
                    std::vector<u16> triangleIndices;
                    
                    BuildBox(halfDimensions, boxVertices, triangleIndices);
                    
                    std::vector<PositionUvVertex> unlitVertices;
                    
                    std::transform(boxVertices.begin(), boxVertices.end(), std::back_inserter(unlitVertices), GeometryHelpersVertexToPositionUvVertex);
                    
                    size_t vertexBufferSizeBytes = sizeof(PositionUvVertex) * unlitVertices.size();
                    size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
                    
                    return new (Eegeo::Rendering::Mesh)(
                                                        vertexLayout,
                                                        glBufferPool,
                                                        unlitVertices.data(),
                                                        vertexBufferSizeBytes,
                                                        triangleIndices.data(),
                                                        indexBufferSizeBytes,
                                                        static_cast<u32>(triangleIndices.size()),
                                                        "UnlitBoxMesh"
                                                        );
                }
                
                BillBoardsMeshRenderable* CreateExampleMeshRenderable(Eegeo::Rendering::Mesh& mesh, Eegeo::Rendering::Materials::IMaterial& material, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool, const Eegeo::dv3 ecefPosition)
                {
                    // A VertexBinding provides association between the fields of our vertex struct (in this case PositionUvVertex), and
                    // corresponding attributes in our shader (in this case TexturedUniformColoredShader, which expects "Position" and "UV" attributes)
                    const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding =
                    vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
                    
                    // Create a WorldMeshRenderable, allowing the mesh to be inserted in render queue and drawn.
                    const Eegeo::Rendering::LayerIds::Values renderLayer = Eegeo::Rendering::LayerIds::InteriorEntities;
                    const bool depthTest = true;
                    const bool alphaBlend = true;
                    const bool translateWithEnvironmentFlattening = false;
                    const bool scaleWithEnvironmentFlattening = false;
                    
                    BillBoardsMeshRenderable* pUnlitBoxRenderable = new BillBoardsMeshRenderable(renderLayer,
                                                                                           ecefPosition,
                                                                                           material,
                                                                                           vertexBinding,
                                                                                           mesh,
                                                                                           Eegeo::Rendering::Colors::WHITE,
                                                                                           depthTest,
                                                                                           alphaBlend,
                                                                                           translateWithEnvironmentFlattening,
                                                                                           scaleWithEnvironmentFlattening);
                    
                    return pUnlitBoxRenderable;
                }
                
                void DeleteRenderable(BillBoardsMeshRenderable* renderable)
                {
                    delete renderable;
                }
                
                Eegeo::m33 BuildBasisToEcef(double originLatitudeDegrees, double originLongitudeDegrees)
                {
                    // create an orthogonal basis centred on originLocation, with positive y axis pointing up aligned with the Earth sphere normal
                    Eegeo::Space::EcefTangentBasis basisFrame;
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                                      Eegeo::Space::LatLong::FromDegrees(originLatitudeDegrees, originLongitudeDegrees).ToECEF(),
                                                                                      90.0,
                                                                                      basisFrame);
                    Eegeo::m33 basisToEcef;
                    basisFrame.GetBasisOrientationAsMatrix(basisToEcef);
                    
                    return basisToEcef;
                }
                
            }
            
            
            MeshExample::MeshExample(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                     Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                                     Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                     Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                     const MeshExampleConfig& config,
                                     //Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                     AppCamera::SdkModel::IAppCameraController& iCameraController)
            
            :m_renderingModule(renderingModule)
            , m_textureFileLoader(textureFileLoader)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_config(config)
            , m_pPositionUvVertexLayout(NULL)
            , m_pShader(NULL)
            , m_pMaterial(NULL)
            , m_pUnlitBoxMesh(NULL)
            , m_basisToEcef(BuildBasisToEcef(config.originLatLong.first, config.originLatLong.second))
            , flag(false)
            //, m_interiorInteractionModel(interiorInteractionModel)
            , m_iCameraController(iCameraController)
            
            {
                
                m_textureInfo.textureId = 0;
                m_textureInfo.width = 0;
                m_textureInfo.height = 0;
                
                m_pPositionUvVertexLayout = CreatePositionUvVertexLayout();
                
                Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
                
                platformRenderableFilters.AddRenderableFilter(*this);
            }
            
            MeshExample::~MeshExample()
            {
                Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
                
                platformRenderableFilters.RemoveRenderableFilter(*this);
                
                delete m_pPositionUvVertexLayout;
                delete m_pMaterial;
                delete m_pShader;
                delete m_pUnlitBoxMesh;
                
                std::for_each(m_renderables.begin(), m_renderables.end(), DeleteRenderable);
                m_renderables.clear();
                
                if (m_textureInfo.textureId != 0)
                {
                    Eegeo_GL(glDeleteTextures(1, &m_textureInfo.textureId));
                }
                
            }
            
            void MeshExample::Start()
            {
                const bool generateMipmaps = true;
                bool success = m_textureFileLoader.LoadTexture(m_textureInfo, m_config.textureFilename, generateMipmaps);
                Eegeo_ASSERT(success, "failed to load texture");
                if (!success)
                    return;
                
                
                m_pShader = Eegeo::Rendering::Shaders::TexturedUniformColoredShader::Create(m_renderingModule.GetShaderIdGenerator().GetNextId());
                
                
                m_pMaterial = new (BillBoardsMeshUnlitTexturedMaterial)(
                                                                     m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                     "MeshExampleMat",
                                                                     *m_pShader,
                                                                     m_textureInfo.textureId
                                                                     );
                
                m_pUnlitBoxMesh = CreateUnlitBoxMesh(m_config.boxWidth, m_config.boxHeight, *m_pPositionUvVertexLayout, m_renderingModule.GetGlBufferPool());
                
                m_renderables.reserve(1);
                
                Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = m_renderingModule.GetVertexBindingPool();
                
                const Eegeo::Space::LatLongAltitude& lla = Eegeo::Space::LatLongAltitude::FromDegrees(
                                                                                                      m_config.originLatLong.first ,
                                                                                                      m_config.originLatLong.second,
                                                                                                      m_config.altitude);
                const Eegeo::dv3& positionEcef = Eegeo::Space::ConvertLatLongAltitudeToEcef(lla);
                BillBoardsMeshRenderable* pRenderable = CreateExampleMeshRenderable(*m_pUnlitBoxMesh, *m_pMaterial, vertexBindingPool, positionEcef);
                
                pRenderable->SetOrientationEcef(m_basisToEcef);
                
                m_renderables.push_back(pRenderable);
                
                
            }
            
            void MeshExample::Update(float dt)
            {
                m_timer += dt;
                /*if(m_timer > 0.5)
                {
                    m_timer = 0;
                    m_renderables.pop_back();
                    updateImage();
                }*/
                
            }
            
            void MeshExample::OnSingleTap(const AppInterface::TapData& data,Eegeo::Collision::AggregateCollisionBvhProvider&collisionBvhProvider)
            {
                /*m_renderables.pop_back();
                updateImage();*/
                
                const Eegeo::Camera::RenderCamera& renderCamera = m_iCameraController.GetRenderCamera();
                
                float screenPixelX = data.point.GetX();
                float screenPixelY = data.point.GetY();
                
                
                Eegeo::dv3 rayDirection;
                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                
                const Eegeo::dv3& rayOrigin = renderCamera.GetEcefLocation();
                Eegeo::Collision::EnvironmentRayCaster *m_pRayCaster = new Eegeo::Collision::EnvironmentRayCaster(collisionBvhProvider, m_environmentFlatteningService);

                const Eegeo::Collision::RayCasterResult& pickResult = m_pRayCaster->CastRay(rayOrigin, rayDirection);
                
                if (pickResult.intersects)
                {
                }

            }
            
            void MeshExample::updateImage()
            {
                const bool generateMipmaps = true;
                bool success = false;
                if(flag)
                {
                    flag = false;
                   success = m_textureFileLoader.LoadTexture(m_textureInfo, "mesh_example/quadrants.png", generateMipmaps);
                }
                else
                {
                    flag = true;
                  success=   m_textureFileLoader.LoadTexture(m_textureInfo, "mesh_example/quadrants_new.png", generateMipmaps);
                }
               
                Eegeo_ASSERT(success, "failed to load texture");
                if (!success)
                    return;
                
                
                m_pShader = Eegeo::Rendering::Shaders::TexturedUniformColoredShader::Create(m_renderingModule.GetShaderIdGenerator().GetNextId());
                
                
                m_pMaterial = new (BillBoardsMeshUnlitTexturedMaterial)(
                                                                        m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                        "MeshExampleMat",
                                                                        *m_pShader,
                                                                        m_textureInfo.textureId
                                                                        );
                
                m_pUnlitBoxMesh = CreateUnlitBoxMesh(m_config.boxWidth, m_config.boxHeight, *m_pPositionUvVertexLayout, m_renderingModule.GetGlBufferPool());
                
                m_renderables.reserve(1);
                
                Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = m_renderingModule.GetVertexBindingPool();
                
                const Eegeo::Space::LatLongAltitude& lla = Eegeo::Space::LatLongAltitude::FromDegrees(
                                                                                                      m_config.originLatLong.first ,
                                                                                                      m_config.originLatLong.second,
                                                                                                      m_config.altitude);
                const Eegeo::dv3& positionEcef = Eegeo::Space::ConvertLatLongAltitudeToEcef(lla);
                BillBoardsMeshRenderable* pRenderable = CreateExampleMeshRenderable(*m_pUnlitBoxMesh, *m_pMaterial, vertexBindingPool, positionEcef);
                
                pRenderable->SetOrientationEcef(m_basisToEcef);
                
                m_renderables.push_back(pRenderable);

            }
            
            
            void MeshExample::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
            {
                const float environmentFlatteningScale = m_environmentFlatteningService.GetCurrentScale();
                const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
                
                const Eegeo::m44& viewProjection = renderCamera.GetViewProjectionMatrix();
                const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
                
                for (BillBoardsMeshRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
                {
                    BillBoardsMeshRenderable& renderable = **iter;
                    
                    const Eegeo::m44& mvp = renderable.CalcModelViewProjection(ecefCameraPosition, viewProjection, environmentFlatteningScale);
                    renderable.SetModelViewProjection(mvp);
                    
                    renderQueue.EnqueueRenderable(renderable);
                }
            }
            
            
        }
    }
    
}
