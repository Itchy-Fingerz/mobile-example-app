// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinSelectionHandler.h"
#include "BidirectionalBus.h"
#include "WayPointModel.h"
#include "CameraTransitionService.h"
namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            class WayPointSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler, private Eegeo::NonCopyable
            {
                WayPointModel &m_wayPointModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                ExampleApp::CameraTransitions::SdkModel::CameraTransitionService& m_cameraTransitionService;

            public:
                WayPointSelectionHandler(WayPointModel& wayPointModel,ExampleAppMessaging::TMessageBus& messageBus,ExampleApp::CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionService);
                
                virtual ~WayPointSelectionHandler();

                void SelectPin();
            };
        }
    }
}