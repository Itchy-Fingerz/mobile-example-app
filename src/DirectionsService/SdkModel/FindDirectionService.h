// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "FindDirectionQuery.h"
#include "FindDirectionHttpRequest.h"
#include "FindDirectionResultJsonParser.h"
#include "FindDirectionHttpRequestFactory.h"
#include "SearchResultModel.h"
#include "BidirectionalBus.h"

#include "IAlertBoxFactory.h"
#include "AlertBox.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "JsonRouteParser.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "DirectionsMenuStateChangedMessage.h"
#include "DirectionMenuFindDirectionMessage.h"
#include "AppGlobeCameraWrapper.h"



namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionService
            {
            private:
                
                Eegeo::Helpers::CallbackCollection1<const DirectionResultModel&> m_findDirectionqueryResponseReceivedCallbacks;
                FindDirectionHttpRequest* m_pCurrentRequest;
                FindDirectionHttpRequestFactory& m_findDirectionHttpRequestFactory;
                Eegeo::Helpers::TCallback0<FindDirectionService> m_handleResponseCallback;
                FindDirectionResultJsonParser& m_findDirectionResultParser;
                Eegeo::Routes::Webservice::JsonRouteParser& m_resultParser;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_pInteriorInteractionModel;
                Eegeo::Routes::RouteService& m_routeService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FindDirectionService> m_failAlertHandler;
                Eegeo::Routes::Style::Thickness::LinearAltitudeBasedRouteThicknessPolicy m_routeThicknessPolicy;
                Eegeo::Helpers::TCallback1<FindDirectionService, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;

                Eegeo::Helpers::TCallback1<FindDirectionService, const DirectionsMenu::DirectionMenuFindDirectionMessage&> m_onFindNewDirectionCallback;

                Eegeo::Helpers::TCallback1<FindDirectionService, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;

                void HandleRouteDirectionResponse();
                void OnFailedToCallRouteResponse();
                void OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);
                void OnFindNewDirection(const DirectionsMenu::DirectionMenuFindDirectionMessage&);
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                bool m_pIsInteriorRoute;
                Eegeo::Routes::RouteRepository& m_routeRepository;
                std::vector<const Eegeo::Routes::Route *> m_routes;
                AppCamera::SdkModel::AppGlobeCameraWrapper& m_cameraWrapper;


            public:
                
                FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,Eegeo::Routes::Webservice::JsonRouteParser& resultParser,Eegeo::Routes::RouteService& routeService,Eegeo::Routes::RouteRepository& routeRepository,Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,FindDirectionResultJsonParser& m_findDirectionResultParser,Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,ExampleAppMessaging::TMessageBus& messageBus, AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper);
                ~FindDirectionService();
                void InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback);
                
                void RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback);
                void PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery);
                void ClearRoutes();
                void Update(float dt);

            };
        }
    }
}