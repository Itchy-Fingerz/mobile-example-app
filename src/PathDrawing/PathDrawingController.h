// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "RouteService.h"
#include "IWayPointsRepository.h"
#include "Route.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "EegeoWorld.h"
#include "IPathDrawingController.h"
#include "AppGlobeCameraWrapper.h"
#include "IWayPointsRepository.h"
#include "DirectionsMenuStateChangedMessage.h"
#include "BidirectionalBus.h"
#include "PathDrawingOptionsModel.h"
#include "DirectionResultModel.h"
#include "DirectionMenuFindDirectionMessage.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        
        class PathDrawingController : public IPathDrawingController
        {
        private:
            PathDrawing::SdkModel::IWayPointsRepository& m_pWayPointsRepository;
            AppCamera::SdkModel::AppGlobeCameraWrapper& m_cameraWrapper;
            ExampleAppMessaging::TMessageBus& m_messageBus;
            
            Menu::View::IMenuSectionViewModel& m_searchSectionViewModel;
            
            Eegeo::Helpers::TCallback1<PathDrawingController, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;
            ExampleApp::PathDrawing::PathDrawingOptionsModel* m_pPathDrawingSettings;

            
            Eegeo::Helpers::TCallback1<PathDrawingController, Menu::View::MenuItemModel> m_onDirectionItemAddedCallback;
            Eegeo::Helpers::TCallback1<PathDrawingController, Menu::View::MenuItemModel> m_onDirectionItemRemovedCallback;
            Eegeo::Helpers::TCallback1<PathDrawingController, const DirectionsMenu::DirectionMenuFindDirectionMessage&> m_onFindNewDirectionCallback;

            
            bool m_createdRoutes;
                        
            
            
            void OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);
            
            void OnSearchItemAdded(Menu::View::MenuItemModel& item);
            
            void OnSearchItemRemoved(Menu::View::MenuItemModel& item);
            
            void OnFindNewDirection(const DirectionsMenu::DirectionMenuFindDirectionMessage&);
            
        public:


            PathDrawingController(Menu::View::IMenuSectionViewModel& searchSectionViewModel
                                  , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                  , PathDrawing::SdkModel::IWayPointsRepository& wayPointsRepository
                                  , ExampleAppMessaging::TMessageBus& messageBus);
            
            void Start() {}
            virtual void Update(float dt);
            void Draw() {}
            void Suspend();
            bool IsRouteCreated();

            void RemoveRoutePlan();

            virtual ~PathDrawingController();
            
        };
    }
}
