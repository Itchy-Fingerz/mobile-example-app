// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "InteriorsExplorerExitMessage.h"
#include "InteractionModelStateChangedMessage.h"
#include "ICameraTransitionController.h"
#include <map>

namespace ExampleApp
{
    namespace InteractionModelStateChangedObserver
    {
        class InteractionModelStateChangedObserver
        {
        private:
            
            ExampleAppMessaging::TMessageBus& m_messageBus;
            Eegeo::Helpers::TCallback1<InteractionModelStateChangedObserver, const InteriorsExplorer::InteriorsExplorerExitMessage&> m_interiorsExplorerExitMessageHandler;
            Eegeo::Helpers::TCallback1<InteractionModelStateChangedObserver, const InteriorsExplorer::InteractionModelStateChangedMessage&> m_InteractionModelStateChangedMessageHandler;
            CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
            std::map<int, Eegeo::dv3> m_floorsLocation;
            std::map<int, float> m_floorsZoomLevel;
            std::map<int, float> m_floorsHeading;
            
            void OnInteriorsExplorerExitMessage(const InteriorsExplorer::InteriorsExplorerExitMessage &message);
            void OnInteractionModelStateChangedMessage(const InteriorsExplorer::InteractionModelStateChangedMessage &message);
            void LoadFloorPositionInfo();
            
        public:
            InteractionModelStateChangedObserver(ExampleAppMessaging::TMessageBus& messageBus,
                                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);
            ~InteractionModelStateChangedObserver();
            
        };
    }
}
