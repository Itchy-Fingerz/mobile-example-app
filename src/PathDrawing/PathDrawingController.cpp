
// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PathDrawingController.h"
#include "RouteBuilder.h"
#include "RouteStyle.h"
#include "WayPointsRepository.h"
#include "WayPointType.h"
#include "LatLongAltitude.h"
#include "IMenuSectionViewModel.h"
#include "IMenuModel.h"
#include "DirectionRouteGeometryModel.h"
#include "SearchResultItemModel.h"


using namespace Eegeo;
using namespace Eegeo::Routes;

namespace ExampleApp
{
    namespace PathDrawing
    {
        

        PathDrawingController::PathDrawingController(Menu::View::IMenuSectionViewModel& searchSectionViewModel
                                                     , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                                     , PathDrawing::SdkModel::IWayPointsRepository& wayPointsRepository
                                                     , ExampleAppMessaging::TMessageBus& messageBus)
        : m_cameraWrapper(cameraWrapper)
        , m_pWayPointsRepository(wayPointsRepository)
        , m_createdRoutes(false)
        , m_messageBus(messageBus)
        , m_searchSectionViewModel(searchSectionViewModel)
        , m_directionsMenuStateChangedCallback(this, &PathDrawingController::OnDirectionsMenuStateChanged)
        , m_onDirectionItemAddedCallback(this, &PathDrawingController::OnSearchItemAdded)
        , m_onDirectionItemRemovedCallback(this, &PathDrawingController::OnSearchItemRemoved)
        , m_onFindNewDirectionCallback(this, &PathDrawingController::OnFindNewDirection)
        {
            m_pPathDrawingSettings = Eegeo_NEW(ExampleApp::PathDrawing::PathDrawingOptionsModel)();
            
            m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            
            Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
            searchSectionMenuModel.InsertItemAddedCallback(m_onDirectionItemAddedCallback);
            searchSectionMenuModel.InsertItemRemovedCallback(m_onDirectionItemRemovedCallback);
            
            m_messageBus.SubscribeNative(m_onFindNewDirectionCallback);

            
            
        }
        
        PathDrawingController::~PathDrawingController()
        {
            Eegeo_DELETE m_pPathDrawingSettings;
            m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
            m_messageBus.UnsubscribeNative(m_onFindNewDirectionCallback);

        }
        
        void PathDrawingController::OnSearchItemAdded(Menu::View::MenuItemModel& item)
        {
            ExampleApp::SearchResultSection::View::SearchResultItemModel &searchItem = (ExampleApp::SearchResultSection::View::SearchResultItemModel&)item.MenuOption();

            Eegeo::Space::LatLong latLongStart = Eegeo::Space::LatLong::FromECEF(searchItem.GetLocationEcef());
           WayPointModel* point = Eegeo_NEW(ExampleApp::PathDrawing::WayPointModel)(searchItem.GetItemIndex()
                                                                         , searchItem.GetWayPointType()
                                                                         , latLongStart
                                                                         , "",searchItem.GetInteriorID(),searchItem.GetFloorIndex(),searchItem.GetIsInterior(),searchItem.GetWayPointNumber());
            m_pWayPointsRepository.AddItem(point); 
        }
        
        void PathDrawingController::OnSearchItemRemoved(Menu::View::MenuItemModel& item)
        {
            ExampleApp::SearchResultSection::View::SearchResultItemModel &searchItem = (ExampleApp::SearchResultSection::View::SearchResultItemModel&)item.MenuOption();

            for (int j = 0; j < m_pWayPointsRepository.GetItemCount(); j++)
            {
                WayPointModel* waypoint = m_pWayPointsRepository.GetItemAtIndex(j);
                if(waypoint->GetWpId() == searchItem.GetItemIndex())
                {
                    m_pWayPointsRepository.RemoveItem(waypoint);
                    Eegeo_DELETE waypoint;
                    break;
                }

            }
        }

        void PathDrawingController::Update(float dt)
        {
        
        }
        
        void PathDrawingController::OnFindNewDirection(const DirectionsMenu::DirectionMenuFindDirectionMessage&)
        {
            if(m_createdRoutes)
            {
               RemoveRoutePlan();
            }
        }

        void PathDrawingController::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
        {
            if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
            {
                RemoveRoutePlan();
            }
        }
        
        void PathDrawingController::RemoveRoutePlan()
        {
            
            while (m_pWayPointsRepository.GetItemCount() != 0)
            {
                WayPointModel* waypoint = m_pWayPointsRepository.GetItemAtIndex(0);
                m_pWayPointsRepository.RemoveItem(waypoint);
                Eegeo_DELETE waypoint;
            }
            m_createdRoutes = false;

        }
        
        bool PathDrawingController::IsRouteCreated()
        {
            return m_createdRoutes;
        }
        
    }
}

