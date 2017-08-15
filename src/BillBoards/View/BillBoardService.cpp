// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "BillBoardService.h"
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
#include "EnvironmentRayCaster.h"
#include "IntersectionTests.h"
#include "InteriorHeightHelpers.h"
#include "CameraHelpers.h"

#include <algorithm>
#include <cmath>
#include "BillBoardSelectedMessage.h"
#include "SetCustomAlertVisibilityMessage.h"
#include "VisualMapService.h"
#include "VisualMapState.h"

#define LINE_TIMEOUT_DURATION 15
#define VIDEO_PLAYBACK_CONST 0.04
#define SPECIAL_OFFER_ALTITUDE 350

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
                
                Eegeo::Rendering::Mesh* CreateUnlitBoxMesh(float width, float height, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool, const BillBoardConfig& config)
                
                {
//                    Eegeo::v3 halfDimensions(width/2, height, width/2);
                    Eegeo::v3 halfDimensions((width/2) * 0.1, height, width/2);
                    std::vector<Vertex> boxVertices;
                    std::vector<u16> triangleIndices;
                    
                    if(config.isSpinner)
                    {
                        BuildSpinnerBox(halfDimensions, boxVertices, triangleIndices, 1);
                    }
                    else if(config.isVideo){
                        BuildVideoBox(halfDimensions, boxVertices, triangleIndices, 2);
//                        BuildBox(halfDimensions, boxVertices, triangleIndices, 2,1);
                    } else {
                        if(config.isVideoFrame)
                            BuildBox(halfDimensions, boxVertices, triangleIndices, 2,1);
                        else
                            BuildBox(halfDimensions, boxVertices, triangleIndices, 2,1);
                    }
                    
                    
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
                
                BillBoardsMeshRenderable* CreateMeshRenderable(Eegeo::Rendering::Mesh& mesh, Eegeo::Rendering::Materials::IMaterial& material, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool, const Eegeo::dv3 ecefPosition)
                {
                    
                    const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding =
                    vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
                    
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
                
                Eegeo::m33 BuildBasisToEcef(double originLatitudeDegrees, double originLongitudeDegrees, double planeRotation)
                {
                    Eegeo::Space::EcefTangentBasis basisFrame;
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                                      Eegeo::Space::LatLong::FromDegrees(originLatitudeDegrees, originLongitudeDegrees).ToECEF(),
                                                                                      planeRotation,
                                                                                      basisFrame);
                    Eegeo::m33 basisToEcef;
                    basisFrame.GetBasisOrientationAsMatrix(basisToEcef);
                    
                    return basisToEcef;
                }
                bool IsBillBoardHidden(const Eegeo::v3 billBoardOrientation, Eegeo::v3 rayDirection)
                {
                    float dotProduct = billBoardOrientation.Dot(rayDirection, billBoardOrientation);
                    if(dotProduct > 0)
                    {
                        return true;
                    }
                    return false;
                }
                void DeleteRenderable(BillBoardsMeshRenderable* renderable)
                {
                    delete renderable;
                }
                
            }
            
            
            BillBoardService::BillBoardService(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                               Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                                               Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                               AppCamera::SdkModel::IAppCameraController& iCameraController,
                                               ExampleApp::PointingQuadRadialLine::QuadLineFactory& lineDrawingFactory,
                                               const Eegeo::Rendering::ScreenProperties& screenProperties,
                                               ExampleAppMessaging::TMessageBus& messageBus)
            
            : m_renderingModule(renderingModule)
            , m_textureFileLoader(textureFileLoader)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_lineDrawingFactory(lineDrawingFactory)
            , m_pPositionUvVertexLayout(NULL)
            , m_pShader(NULL)
            , m_pUnlitBoxMesh(NULL)
            , m_iCameraController(iCameraController)
            , m_selectedConfig()
            , m_quadLine(NULL)
            , m_pVideoAssetReaderService(NULL)
            , m_isSpinnerShown(false)
            , m_isPlayButtonAdded(false)
            , m_currentFloorIndex(-1)
            , m_isSpecialOfferShown(false)
            , m_screenProperties(screenProperties)
            , m_messageBus(messageBus)
            , m_dayTime("Day")
            , m_weather("Default")
            , m_season("Summer")
            {
                
                m_textureInfo.textureId = 0;
                m_textureInfo.width = 0;
                m_textureInfo.height = 0;
                m_timer = 0.0;
                
                m_pPositionUvVertexLayout = CreatePositionUvVertexLayout();
                
                m_pShader = Eegeo::Rendering::Shaders::TexturedUniformColoredShader::Create(m_renderingModule.GetShaderIdGenerator().GetNextId());
                
                Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
                
                platformRenderableFilters.AddRenderableFilter(*this);
                
            }
            
            BillBoardService::~BillBoardService()
            {
                Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
                
                platformRenderableFilters.RemoveRenderableFilter(*this);
                
                delete m_pPositionUvVertexLayout;
                delete m_pShader;
                delete m_pUnlitBoxMesh;
                
                std::for_each(m_renderables.begin(), m_renderables.end(), DeleteRenderable);
                m_renderables.clear();
                
                if (m_textureInfo.textureId != 0)
                {
                    Eegeo_GL(glDeleteTextures(1, &m_textureInfo.textureId));
                }
                
            }
            void BillBoardService::FullRefreshService()
            {
                RemoveAllRenderables();
                StopResetVideoService();                
                m_isSpecialOfferShown = false;
                m_currentFloorIndex = -1;
                m_billBoardConfigList.clear();
            }
            
            void BillBoardService::PartialRefreshService()
            {
                RemoveAllRenderables();
                StopResetVideoService();
                m_isSpecialOfferShown = false;
                
            }
            
            void BillBoardService::AddBillboard(const BillBoardConfig& config)
            {
                if(!IsBillBoardAdded(config))
                {
                    m_billBoardConfigList.push_back(config);
                }
            }
            
            void BillBoardService::CreateBillBoardsFromConfigList()
            {
                
                for (BillBoardsConfigList::const_iterator iter = m_billBoardConfigList.begin(); iter != m_billBoardConfigList.end(); ++iter)
                {
                    const BillBoardConfig& configIter = *iter;
                    if (m_currentFloorIndex == configIter.floorIndex)
                    {
                        CreateBillBoard(configIter);
                    }
                }
                
            }
            
            void BillBoardService::CreateBillBoard(const BillBoardConfig& config)
            {
                
                if (IsEligibleForTimePeriod(config) == true)
                {
                    Eegeo::m33 m_basisToEcef = BuildBasisToEcef(config.originLatLong.first, config.originLatLong.second, config.planeRotation);
                    
                    const bool generateMipmaps = false;
                    bool success = false;
                    
                    success = m_textureFileLoader.LoadTexture(m_textureInfo, config.GetInitialFrame(), generateMipmaps);
                    
                    Eegeo_ASSERT(success, "failed to load texture");
                    if (!success)
                        return;
                    
                  
                    
                    BillBoardsMeshUnlitTexturedMaterial *pMaterial = new (BillBoardsMeshUnlitTexturedMaterial)(
                                                                            m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                            "MeshExampleMat",
                                                                            *m_pShader,
                                                                            m_textureInfo.textureId,
                                                                            *this,
                                                                            config.isVideo
                                                                            );
                    
                    
                    m_pUnlitBoxMesh = CreateUnlitBoxMesh(config.boxWidth, config.boxHeight, *m_pPositionUvVertexLayout, m_renderingModule.GetGlBufferPool(), config);
                    
                    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = m_renderingModule.GetVertexBindingPool();
                    
                    const Eegeo::Space::LatLongAltitude& lla = Eegeo::Space::LatLongAltitude::FromDegrees(
                                                                                                          config.originLatLong.first ,
                                                                                                          config.originLatLong.second,
                                                                                                          config.altitude);
                    const Eegeo::dv3& positionEcef = Eegeo::Space::ConvertLatLongAltitudeToEcef(lla);
                    BillBoardsMeshRenderable* pRenderable = CreateMeshRenderable(*m_pUnlitBoxMesh, *pMaterial, vertexBindingPool, positionEcef);
                    
                    pRenderable->SetOrientationEcef(m_basisToEcef);
                    pRenderable->SetConfig(config);
                    
                    m_renderables.push_back(pRenderable);
                    m_pUnlitBoxMesh = NULL;
                    pMaterial = NULL;
                }
            }
            
            bool BillBoardService::IsEligibleForTimePeriod(const BillBoardConfig& config)
            {
                
                if(m_dayTime == config.dayTime && m_weather == config.weather && m_season == config.season)
                    return true;
                
                return false;                
            }
            
            void BillBoardService::RenderVideoBillBoard()
            {
                if(!m_pVideoAssetReaderService->IsVideoEnded())
                {
                    m_pVideoAssetReaderService->RenderVideoBillBoard();
                }
                else
                    StopResetVideoService();
            }
            
            void BillBoardService::SetFloorIndex(int floor_index)
            {
                m_currentFloorIndex = floor_index;
            }
            
            void BillBoardService::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
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
            
            void BillBoardService::OnSingleTap(const AppInterface::TapData& data)
            {
                if (IsInterSectingWithBillBoard(data, m_selectedConfig))
                {
                    DrawLine(m_selectedConfig);
                    m_messageBus.Publish(BillBoardSelectedMessage(m_selectedConfig.poiID, m_selectedConfig.unique_tag));
                }
            }
            
            bool BillBoardService::IsInterSectingWithBillBoard(const AppInterface::TapData& data, BillBoardConfig &out_config)
            {
                
                const Eegeo::Camera::RenderCamera& renderCamera = m_iCameraController.GetRenderCamera();
                
                float screenPixelX = data.point.GetX();
                float screenPixelY = data.point.GetY();
                
                Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
                Eegeo::dv3 rayDirection;
                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                
                bool isIntersecting = false;
                
                for (BillBoardsMeshRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
                {
                    BillBoardsMeshRenderable& renderable = **iter;
                    const Eegeo::Space::LatLongAltitude& lla = Eegeo::Space::LatLongAltitude::FromDegrees(  renderable.GetConfig().originLatLong.first ,
                                                                                                          renderable.GetConfig().originLatLong.second,
                                                                                                          renderable.GetConfig().altitude);
                    
                    const Eegeo::dv3& originNormal = Eegeo::Space::ConvertLatLongAltitudeToEcef(lla);
                    isIntersecting = Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, originNormal, renderable.GetConfig().boxWidth);
                    if(isIntersecting)
                    {
                        if(IsBillBoardHidden(renderable.GetForwardVector(), rayDirection.ToSingle()))
                        {
                            isIntersecting = false;
                            continue;
                        }
                        
                        if(renderable.GetConfig().isVideo)
                        {
                            if(renderable.GetConfig().IsInStoppedState())
                            {
                                out_config = renderable.GetConfig();
                                StopResetVideoService();
                                renderable.GetConfig().isAnimating = true;
                                m_pVideoAssetReaderService->StartReading(renderable.GetConfig().videoURL);
                                
                                const BillBoardsMeshUnlitTexturedMaterial* tempMaterial =(BillBoardsMeshUnlitTexturedMaterial*)renderable.GetMaterial();
                                if(m_pVideoAssetReaderService !=NULL)
                                {
                                    tempMaterial->SetAnimatingState(true);
                                }
                                
                                tempMaterial->SetTappedState(true);
                                break;
                            }
                            
                            else if(renderable.GetConfig().IsInPlayingState())
                            {
                                out_config = renderable.GetConfig();
                                renderable.GetConfig().isPaused = true;
                                renderable.GetConfig().isAnimating = false;
                                m_pVideoAssetReaderService->PausePlayer();
                                break;
                            }
                            
                            else if(renderable.GetConfig().IsInPausedState())
                            {
                                out_config = renderable.GetConfig();
                                renderable.GetConfig().isPaused = false;
                                renderable.GetConfig().isAnimating = true;
                                m_pVideoAssetReaderService->ContinueAfterPause();
                                
                                const BillBoardsMeshUnlitTexturedMaterial* tempMaterial =(BillBoardsMeshUnlitTexturedMaterial*)renderable.GetMaterial();
                                if(m_pVideoAssetReaderService !=NULL)
                                {
                                    tempMaterial->SetAnimatingState(true);
                                }
                                break;
                            }
                        }

                        if(isIntersecting)
                        {
                            out_config = renderable.GetConfig();
                            const BillBoardsMeshUnlitTexturedMaterial* pMaterial = (BillBoardsMeshUnlitTexturedMaterial*)renderable.GetMaterial();
                            pMaterial->SetTappedState(true);
                            break;
                        }
                    }
                    
                }
                
                return isIntersecting;
            }

            void BillBoardService::Update(float dt)
            {
                
                m_timer += dt;
                
                if(m_timer > VIDEO_PLAYBACK_CONST)
                {
                    m_timer = 0;
                    
                    for (BillBoardsMeshRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
                    {
                        BillBoardsMeshRenderable& renderable = **iter;
                        const BillBoardsMeshUnlitTexturedMaterial* tempMaterial =(BillBoardsMeshUnlitTexturedMaterial*)renderable.GetMaterial();
                        
                        if(renderable.GetConfig().isSpinner)
                        {
                            m_textureFileLoader.LoadTexture(m_textureInfo, renderable.GetConfig().GetNextFrame(), true);
                            tempMaterial->SetTextureId(m_textureInfo.textureId);
                        }
                        
                        if(renderable.GetConfig().isVideo)
                        {
                            
                            if(tempMaterial->GetAnimatingState())
                            {
                                
                                if(!m_pVideoAssetReaderService->GetHasStartedPlayingFlagStatus() && !m_isSpinnerShown)
                                {
                                    AddSpinner(renderable.GetConfig());
                                }
                                
                                if(m_pVideoAssetReaderService->GetIsPausedForBufferingFlagStatus() != m_isSpinnerShown)
                                {
                                    if(m_pVideoAssetReaderService->GetIsPausedForBufferingFlagStatus())
                                    {
                                        AddSpinner(renderable.GetConfig());
                                    }
                                }
                                if(m_pVideoAssetReaderService->GetHasStartedPlayingFlagStatus() && !m_pVideoAssetReaderService->GetIsPausedForBufferingFlagStatus() && m_isSpinnerShown)
                                {
                                    RemoveSpinner();
                                }
                                
                                if(m_pVideoAssetReaderService->GetIsPausedByUserFlagStatus() && m_isSpinnerShown)
                                {
                                    RemoveSpinner();
                                }
                            }
                            
                            if(m_pVideoAssetReaderService->GetIsPausedByUserFlagStatus() && !m_isPlayButtonAdded)
                            {
                                m_isPlayButtonAdded = true;
                                AddPlayButton(renderable.GetConfig());
                                
                            }
                            
                            else if (!m_pVideoAssetReaderService->GetIsPausedByUserFlagStatus() && m_isPlayButtonAdded)
                            {
                                RemovePlayButton();
                            }
                            
                            if (renderable.GetConfig().IsInPlayingState() || m_pVideoAssetReaderService->GetIsPausedByUserFlagStatus())
                            {
                                const Eegeo::Camera::RenderCamera& renderCamera = m_iCameraController.GetRenderCamera();
                                float screenPixelX = m_screenProperties.GetScreenWidth() / 2;
                                float screenPixelY = m_screenProperties.GetScreenHeight() / 2;
                                Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
                                Eegeo::dv3 rayDirection;
                                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                                
                                if(IsBillBoardHidden(renderable.GetForwardVector(), rayDirection.ToSingle()))
                                {
                                    StopResetVideoService();
                                    continue;
                                }
                            }
                            
                        }
                    
                        if(renderable.GetConfig().isSpecialOffer && !m_isSpecialOfferShown)
                        {
                            SpecialOffersTriger(renderable);
                        }
                    }
                }
                
                if(m_quadLine != NULL)
                {
                    CheckLineDrawingTimmedOut();
                }
            }
            
            void BillBoardService::SpecialOffersTriger(BillBoardsMeshRenderable& renderable)
            {
                const Eegeo::Camera::RenderCamera& renderCamera = m_iCameraController.GetRenderCamera();
                if(renderCamera.GetAltitude() < SPECIAL_OFFER_ALTITUDE)
                {
                Eegeo::v3 resultCoordinates = Eegeo::Camera::CameraHelpers::GetScreenPositionFromLatLong(Eegeo::Space::LatLong::FromDegrees(renderable.GetConfig().originLatLong.first,renderable.GetConfig().originLatLong.second), renderCamera);
                    
                    if(resultCoordinates.GetX() > 0 && resultCoordinates.GetX() < m_screenProperties.GetScreenWidth() && resultCoordinates.GetY() > 0 && m_screenProperties.GetScreenHeight())
                    {
                        m_isSpecialOfferShown = true;
                        m_messageBus.Publish(ExampleApp::CustomAlert::SetCustomAlertVisibilityMessage(true));
                    }
                }
            }
            
            void BillBoardService::SetVideoService(ExampleApp::VideoAssetReader::VideoAssetReaderService &service)
            {
                m_pVideoAssetReaderService = &service;
            } 
            
            void BillBoardService::StopResetVideoService()
            {
                ResetAnimatingFlag();
                m_pVideoAssetReaderService->ResetPlayer();
                RemovePlayButton();
                RemoveSpinner();
            }
            
            void BillBoardService::AddSpinner(const BillBoardConfig& config)
            {
                BillBoards::View::BillBoardConfig tempConfig;
                
                tempConfig.billBoardId = 100;
                tempConfig.textureFilename = "loading";
                tempConfig.numberOfFrames = 12;
                tempConfig.originLatLong = config.originLatLong;
                tempConfig.lineEndTo = config.lineEndTo;
                tempConfig.altitude = config.altitude;
                tempConfig.boxWidth = 18.75f/1.5;
                tempConfig.boxHeight = 12.5f/1.5;
                tempConfig.planeRotation = config.planeRotation;
                tempConfig.floorIndex = config.floorIndex;
                tempConfig.isSpinner = true;
                tempConfig.highlightColor = config.highlightColor;
                tempConfig.dayTime = config.dayTime;
                tempConfig.weather = config.weather;
                tempConfig.season = config.season;
                
                CreateBillBoard(tempConfig);
                
                m_isSpinnerShown = true;
            }
            
            void BillBoardService::RemoveSpinner()
            {
                for (BillBoardsMeshRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
                {
                    BillBoardsMeshRenderable& renderable = **iter;
                    
                    if(renderable.GetConfig().isSpinner)
                    {
                        m_renderables.erase(iter);
                        break;
                    }
                }
                
                m_isSpinnerShown = false;
            }
            
            void BillBoardService::AddPlayButton(const BillBoardConfig& config)
            {
                BillBoards::View::BillBoardConfig tempConfig;
                
                tempConfig.billBoardId = 101;
                tempConfig.textureFilename = "play_btn";
                tempConfig.originLatLong = config.originLatLong;
                tempConfig.lineEndTo = config.lineEndTo;
                tempConfig.altitude = config.altitude;
                tempConfig.boxWidth = 18.75f/1.5;
                tempConfig.boxHeight = 12.5f/1.5;
                tempConfig.planeRotation = config.planeRotation;
                tempConfig.floorIndex = config.floorIndex;
                tempConfig.dayTime = config.dayTime;   // 24 hours clock 7:00
                tempConfig.weather = config.weather;
                tempConfig.season = config.season;
                tempConfig.isPlayBtn = true;
                tempConfig.highlightColor = config.highlightColor;

                
                CreateBillBoard(tempConfig);
                
                m_isPlayButtonAdded = true;
            }

            void BillBoardService::RemovePlayButton()
            {
                for (BillBoardsMeshRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
                {
                    BillBoardsMeshRenderable& renderable = **iter;
                    
                    if(renderable.GetConfig().isPlayBtn)
                    {
                        m_renderables.erase(iter);
                        break;
                    }
                }
                
                m_isPlayButtonAdded = false;
            }
            
            void BillBoardService::DrawLine(const BillBoardConfig& config)
            {
                
                RemoveLine();
                
                m_quadLine = m_lineDrawingFactory.CreateQuadLine(config.highlightColor,
                                                                 Eegeo::Space::LatLongAltitude::FromDegrees(config.originLatLong.first,config.originLatLong.second,config.altitude),
                                                                 Eegeo::Space::LatLongAltitude::FromDegrees(config.lineEndTo.first,config.lineEndTo.second,config.altitude-10),
                                                                 2.5f,
                                                                 1.5f
                                                                 );
                m_startTime = std::chrono::system_clock::now();
            }
            
            void BillBoardService::CheckLineDrawingTimmedOut()
            {
                std::chrono::time_point<std::chrono::system_clock> currentTime;
                currentTime = std::chrono::system_clock::now();
                std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
                std::time_t startTime_t = std::chrono::system_clock::to_time_t(m_startTime);
                double diff = difftime(currentTime_t, startTime_t);
                if(diff >= LINE_TIMEOUT_DURATION)
                {
                    RemoveLine();
                }
            }
            
            void BillBoardService::RemoveLine()
            {
                if(m_quadLine != NULL)
                {
                    Eegeo_DELETE m_quadLine;
                    m_quadLine = NULL;
                }
            }
            
            void BillBoardService::ResetAnimatingFlag()
            {
                for (BillBoardsMeshRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
                {
                    BillBoardsMeshRenderable& renderable = **iter;
                    
                    renderable.GetConfig().isAnimating = false;
                    renderable.GetConfig().isPaused = false;
                    
                    const BillBoardsMeshUnlitTexturedMaterial* tempMaterial =(BillBoardsMeshUnlitTexturedMaterial*)renderable.GetMaterial();
                    tempMaterial->SetAnimatingState(false);
                    tempMaterial->SetTappedState(false);
                }
            }
            
            void BillBoardService::RemoveAllRenderables()
            {
                
                if(m_quadLine != NULL)
                {
                    RemoveLine();
                }                

                std::for_each(m_renderables.begin(), m_renderables.end(), DeleteRenderable);
                m_renderables.clear();
                
                if (m_textureInfo.textureId != 0)
                {
                    Eegeo_GL(glDeleteTextures(1, &m_textureInfo.textureId));
                }

            }
            
            bool BillBoardService::IsBillBoardAdded(const BillBoardConfig& config)
            {
                
                bool isAlreadyAdded = false;
                
                for (BillBoardsConfigList::const_iterator iter = m_billBoardConfigList.begin(); iter != m_billBoardConfigList.end(); ++iter)
                {
                    const BillBoardConfig& configIter = *iter;
                    if (config.billBoardId == configIter.billBoardId)
                    {
                        isAlreadyAdded = true;
                    }
                }
                
                return isAlreadyAdded;
                
            }
            
        }
    }
}
