// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BillBoards.h"
#include "RenderTexture.h"
#include "Rendering.h"
#include "Modules.h"
#include "Helpers.h"
#include "DebugRenderer.h"
#include "BillBoardService.h"
#include "AggregateCollisionBvhProvider.h"
#include "BillBoardInteriorStateChangedObserver.h"
#include "QuadLineFactory.h"
#include "BillBoardWeatherStateChangedObserver.h"
#include "BillBoardShowOffersSelectionObserver.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            class BillBoardsModule
            {
            private:
                
                ExampleApp::BillBoards::SdkModel::BillBoardsRepository* m_pBillBoardsRepository;
                ExampleApp::PointingQuadRadialLine::QuadLineFactory* m_pQuadLineFactory;
                
                Eegeo::Modules::Core::RenderingModule& m_renderingModule;
                Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
                Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                BillBoards::View::BillBoardService *m_pBillBoardService;
                AppCamera::SdkModel::IAppCameraController& m_iCameraController;
                SdkModel::BillBoardInteriorStateChangedObserver* m_pFloorChangeObserver;
                
                SdkModel::BillBoardWeatherStateChangedObserver * m_pWeatherChangeObserver;
                SdkModel::BillBoardShowOffersSelectionObserver * m_pShowOffersSelectionObserver;
                
            public:
                BillBoardsModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                 Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                 Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                                 Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                 AppCamera::SdkModel::IAppCameraController& iCameraController,
                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                 Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule,
                                 PathDrawing::SdkModel::WayPointOnMapModel &wayPointModel,
                                 Direction::SdkModel::FindDirectionService &findDirectionService,
                                 Menu::View::IMenuViewModel& directionViewModel,
                                 ExampleAppMessaging::TMessageBus& messageBus);
                ~BillBoardsModule();
                
                ExampleApp::BillBoards::SdkModel::BillBoardsRepository& GetBillBoardRepository()
                {
                    return *m_pBillBoardsRepository;
                }
                BillBoards::View::BillBoardService& GetBillBoardService()
                {
                    return *m_pBillBoardService;
                }
            };
        }
    }
}
