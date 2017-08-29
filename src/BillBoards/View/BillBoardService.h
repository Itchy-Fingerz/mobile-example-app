// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"
#include "BillBoardConfig.h"
#include "RenderTexture.h"
#include "Rendering.h"
#include "Modules.h"
#include "Helpers.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"

#include "VectorMath.h"
#include <list>
#include "AppInterface.h"
#include "IAppCameraController.h"
#include "QuadLine.h"
#include "QuadLineFactory.h"
#include "VideoAssetReaderService.h"
#include "VisualMap.h"

namespace ExampleApp
{
    
    namespace BillBoards
    {
        namespace View
        {
            class BillBoardsMeshRenderable;
            class BillBoardsMeshUnlitTexturedMaterial;
            
            
            class BillBoardService : public Eegeo::Rendering::IRenderableFilter
            {
            public:
                typedef std::list<BillBoardsMeshRenderable*> BillBoardsMeshRenderableVector;
                typedef std::list<BillBoardConfig> BillBoardsConfigList;

                
                BillBoardService(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                 Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                                 Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                 AppCamera::SdkModel::IAppCameraController& iCameraController,
                                 ExampleApp::PointingQuadRadialLine::QuadLineFactory& lineDrawingFactory,
                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                 ExampleAppMessaging::TMessageBus& messageBus);
                virtual ~BillBoardService();
                
                void Update(float dt);
                
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
                void AddBillboard(const BillBoardConfig& config);
                void OnSingleTap(const AppInterface::TapData& data);
                
                void SetFloorIndex(int floor_index);
                int GetFloorIndex();
                void RemoveAllRenderables();
                void SetUpTexture(GLuint texture);
                void SetVideoService(ExampleApp::VideoAssetReader::VideoAssetReaderService &service);
                void RenderVideoBillBoard();
                void StopResetVideoService();
                void ResetAnimatingFlag();

                void OnFloorChange(int floorIndex);
                void OnWeatherStateChange();
                void CreateBillBoardsFromConfigList();
                void OnInteriorsExit();
                
                void SetDayTime(std::string dayTime)
                {
                    m_dayTime = dayTime;
                }
                void SetWeather(std::string weather)
                {
                    m_weather = weather;
                }
                void SetSeason(std::string season)
                {
                    m_season = season;
                }
                
                void ShowSpecialOfferBillBoardsOnly();
                
            private:
                
                bool m_isSpinnerShown;
                bool m_isPlayButtonAdded;
                bool m_isSpecialOfferShown;
                float m_timer;
                int m_currentFloorIndex;
                std::string m_dayTime;
                std::string m_weather;
                std::string m_season;
                
                Eegeo::Modules::Core::RenderingModule& m_renderingModule;
                Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                
                ExampleApp::PointingQuadRadialLine::QuadLineFactory& m_lineDrawingFactory;
                Eegeo::Helpers::GLHelpers::TextureInfo m_textureInfo;
                
                Eegeo::Rendering::VertexLayouts::VertexLayout* m_pPositionUvVertexLayout;
                Eegeo::Rendering::Shaders::TexturedUniformColoredShader* m_pShader;
                Eegeo::Rendering::Mesh* m_pUnlitBoxMesh;
                BillBoardsMeshRenderableVector m_renderables;
                BillBoardsConfigList m_billBoardConfigList;
                BillBoardConfig m_selectedConfig;
                
                const Eegeo::Rendering::ScreenProperties& m_screenProperties;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                bool IsInterSectingWithBillBoard(const AppInterface::TapData& data, BillBoardConfig &out_config);
                
                void CreateBillBoard(const BillBoardConfig& config);
                bool IsEligibleForTimePeriod(const BillBoardConfig& config);
                void CheckLineDrawingTimmedOut();
                void DrawLine(const BillBoardConfig& config);
                void RemoveLine();
                
                void AddSpinner(const BillBoardConfig& config);
                void AddPlayButton(const BillBoardConfig& config);
                
                void RemovePlayButton();
                void RemoveSpinner();
                bool IsBillBoardAdded(const BillBoardConfig& config);
                
                AppCamera::SdkModel::IAppCameraController& m_iCameraController;
                
                std::chrono::time_point<std::chrono::system_clock> m_startTime;
                ExampleApp::PointingQuadRadialLine::QuadLine* m_quadLine;
                
                ExampleApp::VideoAssetReader::VideoAssetReaderService *m_pVideoAssetReaderService;
                
                void SpecialOffersTriger(BillBoardsMeshRenderable& renderable);
            };
        }
    }
}
