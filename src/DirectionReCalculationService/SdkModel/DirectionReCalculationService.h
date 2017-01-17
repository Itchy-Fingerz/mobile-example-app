// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "BidirectionalBus.h"
#include "IPathDrawingController.h"
#include "DirectionsMenuStateChangedMessage.h"
#include "Route.h"



namespace ExampleApp
{
    namespace DirectionReCalculationService
    {
        namespace SdkModel
        {
            class DirectionReCalculationService
            {
            private:
                
                Eegeo::Location::ILocationService& m_locationService;
                ExampleApp::PathDrawing::IPathDrawingController& m_pathDrawingController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool m_shouldReCalculate;
                
                
                Eegeo::Helpers::TCallback1<DirectionReCalculationService, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;
                void OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);

                Eegeo::Routes::RouteRepository& m_routeRepository;
            
            public:
                
                DirectionReCalculationService(Eegeo::Location::ILocationService& locationService,ExampleApp::PathDrawing::IPathDrawingController& pathDrawingController, ExampleAppMessaging::TMessageBus& messageBus,Eegeo::Routes::RouteRepository& routeRepository);
                ~DirectionReCalculationService();
                void Update(float dt);
            };
        }
    }
}