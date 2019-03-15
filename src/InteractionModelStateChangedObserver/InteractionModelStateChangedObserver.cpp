// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteractionModelStateChangedObserver.h"

namespace ExampleApp
{
    namespace InteractionModelStateChangedObserver
    {
        InteractionModelStateChangedObserver::InteractionModelStateChangedObserver(ExampleAppMessaging::TMessageBus& messageBus,
                                                                                   CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
        : m_messageBus(messageBus)
        , m_cameraTransitionController(cameraTransitionController)
        , m_interiorsExplorerExitMessageHandler(this,&InteractionModelStateChangedObserver::OnInteriorsExplorerExitMessage)
        , m_InteractionModelStateChangedMessageHandler(this,&InteractionModelStateChangedObserver::OnInteractionModelStateChangedMessage)
        {
            m_messageBus.SubscribeNative(m_interiorsExplorerExitMessageHandler);
            m_messageBus.SubscribeUi(m_InteractionModelStateChangedMessageHandler);
            InteractionModelStateChangedObserver::LoadFloorPositionInfo();
        }
        
        InteractionModelStateChangedObserver::~InteractionModelStateChangedObserver()
        {
            m_messageBus.UnsubscribeNative(m_interiorsExplorerExitMessageHandler);
            m_messageBus.UnsubscribeUi(m_InteractionModelStateChangedMessageHandler);
        }
        
        void InteractionModelStateChangedObserver::OnInteriorsExplorerExitMessage(const InteriorsExplorer::InteriorsExplorerExitMessage &message)
        {
        }
        
        void InteractionModelStateChangedObserver::OnInteractionModelStateChangedMessage(const InteriorsExplorer::InteractionModelStateChangedMessage &message)
        {
            
            if (message.GetInteriorID().Value() == "EIM-1daffd08-49d0-476d-866f-23a52f45713c" && !m_cameraTransitionController.IsTransitioning())
            {
                int selectedFloorIndex = message.GetSelectedFloorIndex();
                const Eegeo::dv3 interestPoint = m_floorsLocation.find(selectedFloorIndex)->second;
                const float distanceFromInterestPoint = m_floorsZoomLevel.find(selectedFloorIndex)->second;
                const float heading = m_floorsHeading.find(message.GetSelectedFloorIndex())->second;
                
                m_cameraTransitionController.StartTransitionTo(interestPoint,
                                                               distanceFromInterestPoint,
                                                               heading,
                                                               message.GetInteriorID(),
                                                               message.GetSelectedFloorIndex(),
                                                               true,
                                                               true,
                                                               true,
                                                               true);
            }

        }
        
        void InteractionModelStateChangedObserver::LoadFloorPositionInfo()
        {
            Eegeo::Space::LatLong loc = Eegeo::Space::LatLong::FromDegrees(26.155182498890433, -78.79226548085914);
            const Eegeo::dv3 interestPoint = loc.ToECEF();
            float heading = Eegeo::Math::Deg2Rad(78.4);

            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(0,interestPoint));
            m_floorsZoomLevel.insert(std::pair<int, float>(0,250.2683410644531));
            m_floorsHeading.insert(std::pair<int, float>(0,heading));
            
            Eegeo::Space::LatLong locFloor1 = Eegeo::Space::LatLong::FromDegrees(26.155182498890433, -78.79272541218683);
            Eegeo::dv3 interest1 = locFloor1.ToECEF();
            heading = Eegeo::Math::Deg2Rad(78.0);
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(1,interest1));
            m_floorsZoomLevel.insert(std::pair<int, float>(1,274.0));
            m_floorsHeading.insert(std::pair<int, float>(1,heading));
            
            
            const Eegeo::Space::LatLong locFloor2 = Eegeo::Space::LatLong::FromDegrees(26.15516638853986, -78.79241370024458);
            const Eegeo::dv3 interest2 = locFloor2.ToECEF();
            heading = Eegeo::Math::Deg2Rad(75.4);

            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(2,interest2));
            m_floorsZoomLevel.insert(std::pair<int, float>(2,270));
            m_floorsHeading.insert(std::pair<int, float>(2,heading));
            
            heading = Eegeo::Math::Deg2Rad(75.4);
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(3,interest2));
            m_floorsZoomLevel.insert(std::pair<int, float>(3,240));
            m_floorsHeading.insert(std::pair<int, float>(3,heading));
            
            const Eegeo::dv3 interest4 = Eegeo::Space::LatLong::FromDegrees(26.155162289253884, -78.79261573860019).ToECEF();
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(4,interest4));
            m_floorsZoomLevel.insert(std::pair<int, float>(4,270));
            m_floorsHeading.insert(std::pair<int, float>(4,heading));
            
            const Eegeo::dv3 interest5 = Eegeo::Space::LatLong::FromDegrees(26.155174559849932, -78.79256372777634).ToECEF();
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(5,interest5));
            m_floorsZoomLevel.insert(std::pair<int, float>(5,230));
            m_floorsHeading.insert(std::pair<int, float>(5,heading));
            
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(6,interest5));
            m_floorsZoomLevel.insert(std::pair<int, float>(6,230));
            m_floorsHeading.insert(std::pair<int, float>(6,heading));
            
            const Eegeo::dv3 interest6 = Eegeo::Space::LatLong::FromDegrees(26.15518430381195, -78.79257448642157).ToECEF();
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(7,interest6));
            m_floorsZoomLevel.insert(std::pair<int, float>(7,230));
            m_floorsHeading.insert(std::pair<int, float>(7,heading));
            
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(8,interest6));
            m_floorsZoomLevel.insert(std::pair<int, float>(8,230));
            m_floorsHeading.insert(std::pair<int, float>(8,heading));
            
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(9,interest6));
            m_floorsZoomLevel.insert(std::pair<int, float>(9,230));
            m_floorsHeading.insert(std::pair<int, float>(9,heading));
            
            const Eegeo::dv3 interestPoint10 = Eegeo::Space::LatLong::FromDegrees(26.155175702389037, -78.79273714772093).ToECEF();
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(10,interestPoint10));
            m_floorsZoomLevel.insert(std::pair<int, float>(10,270));
            m_floorsHeading.insert(std::pair<int, float>(10,heading));

            heading = Eegeo::Math::Deg2Rad(78.4);
            const Eegeo::dv3 interestPoint12 = Eegeo::Space::LatLong::FromDegrees(26.155147247944303, -78.79300009889178).ToECEF();
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(11,interestPoint12));
            m_floorsZoomLevel.insert(std::pair<int, float>(11,220));
            m_floorsHeading.insert(std::pair<int, float>(11,heading));
            
            const Eegeo::dv3 interestPoint13 = Eegeo::Space::LatLong::FromDegrees(26.155135715755936, -78.79304823530377).ToECEF();
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(12,interestPoint13));
            m_floorsZoomLevel.insert(std::pair<int, float>(12,210));
            m_floorsHeading.insert(std::pair<int, float>(12,heading));
            
            m_floorsLocation.insert(std::pair<int, Eegeo::dv3>(13,interestPoint13));
            m_floorsZoomLevel.insert(std::pair<int, float>(13,225));
            m_floorsHeading.insert(std::pair<int, float>(13,heading));
            
        }
        
    }
}

