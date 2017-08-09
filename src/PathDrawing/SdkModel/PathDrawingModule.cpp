// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PathDrawingModule.h"
#include "WayPointsRepository.h"
#include "LatLongAltitude.h"
#include "WayPointType.h"
#include "PathDrawingController.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {

            PathDrawingModule::PathDrawingModule(Menu::View::IMenuSectionViewModel& searchSectionViewModel,WorldPins::SdkModel::IWorldPinsService& worldPinsService
                                                                 , Eegeo::Routes::RouteService& routeService
                                                                 , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                                                 , TagSearch::ISearchResultIconKeyMapper& searchResultIconCategoryMapper
                                                                 , ExampleAppMessaging::TMessageBus& messageBus
                                                                , ExampleApp::CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionService)
            
            {
                m_pWayPointsRepository = Eegeo_NEW(WayPointsRepository);
                m_pPathDrawingController = Eegeo_NEW(ExampleApp::PathDrawing::PathDrawingController)(searchSectionViewModel
                                                                                                     , cameraWrapper
                                                                                                     , *m_pWayPointsRepository
                                                                                                     , messageBus);
                
                m_pWayPointOnMapModel = Eegeo_NEW(ExampleApp::PathDrawing::SdkModel::WayPointOnMapModel)(worldPinsService
                                                                                                         , searchResultIconCategoryMapper
                                                                                                         , *m_pWayPointsRepository
                                                                                                         , messageBus
                                                                                                         , cameraTransitionService);
                            }
            
            PathDrawingModule::~PathDrawingModule()
            {                
                Eegeo_DELETE m_pWayPointsRepository;
                Eegeo_DELETE m_pPathDrawingController;
                Eegeo_DELETE m_pWayPointOnMapModel;
            }

            IWayPointsRepository& PathDrawingModule::GetWayPointsRepository() const
            {
                return *m_pWayPointsRepository;
            }
            
            IPathDrawingController& PathDrawingModule::GetPathDrawingController() const
            {
                return *m_pPathDrawingController;
            }
            
            WayPointOnMapModel& PathDrawingModule::GetWayPointOnMapModel() const
            {
                return *m_pWayPointOnMapModel;
            }

            void PathDrawingModule::Update(float dt)
            {
                
            }
        }
    }
}
