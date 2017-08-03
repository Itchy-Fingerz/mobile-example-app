// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Types.h"
#include "BillBoardsModule.h"
#include "BillBoardsRepository.h"
#include "BillBoardsController.h"
#include "QuadLineFactory.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            BillBoardsModule::BillBoardsModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                               Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                               Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                                               Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                               AppCamera::SdkModel::IAppCameraController& iCameraController,
                                               const Eegeo::Rendering::ScreenProperties& screenProperties,
                                               Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule,
                                               ExampleAppMessaging::TMessageBus& messageBus)
            :m_renderingModule(renderingModule)
            , m_debugRenderer(debugRenderer)
            ,m_textureFileLoader(textureFileLoader)
            ,m_environmentFlatteningService(environmentFlatteningService)
            ,m_iCameraController(iCameraController)
            {
                m_pBillBoardsRepository = Eegeo_NEW(ExampleApp::BillBoards::SdkModel::BillBoardsRepository)();
                
                m_pQuadLineFactory = Eegeo_NEW(ExampleApp::PointingQuadRadialLine::QuadLineFactory)
                (m_renderingModule,
                                                                           m_debugRenderer,
                                                                           m_environmentFlatteningService);
                
                m_pBillBoardService = Eegeo_NEW(BillBoards::View::BillBoardService)(m_renderingModule,
                                                                             m_textureFileLoader,
                                                                             m_environmentFlatteningService,
                                                                             m_iCameraController,
                                                                             *m_pQuadLineFactory,
                                                                             screenProperties,
                                                                             messageBus);

                
                m_pFloorChangeObserver = Eegeo_NEW(SdkModel::BillBoardInteriorStateChangedObserver)(messageBus,*m_pBillBoardService,interiorsPresentationModule);

                m_pWeatherChangeObserver = Eegeo_NEW(SdkModel::BillBoardWeatherStateChangedObserver)(messageBus,*m_pBillBoardService);
            }
            
            BillBoardsModule::~BillBoardsModule()
            {
                Eegeo_DELETE m_pBillBoardsRepository;
                Eegeo_DELETE m_pBillBoardService;
                Eegeo_DELETE m_pFloorChangeObserver;
                Eegeo_DELETE m_pQuadLineFactory;
                Eegeo_DELETE m_pWeatherChangeObserver;
            }
            
        }
    }
}
