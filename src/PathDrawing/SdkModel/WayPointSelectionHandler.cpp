// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointSelectionHandler.h"
#include "DirectionsMenuItemHighlightMessage.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            WayPointSelectionHandler::WayPointSelectionHandler(WayPointModel& wayPointModel,ExampleAppMessaging::TMessageBus& messageBus,ExampleApp::CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionService)
            :m_wayPointModel(wayPointModel)
            ,m_messageBus(messageBus)
            ,m_cameraTransitionService(cameraTransitionService)
            
            {
            
            }
            
            WayPointSelectionHandler::~WayPointSelectionHandler()
            {
            
            }
            
            void WayPointSelectionHandler::SelectPin()
            {
                if (m_wayPointModel.GetType() == ExampleApp::PathDrawing::WayPointType::Elevator)
                {
                    m_cameraTransitionService.StartTransitionTo(100.0, m_wayPointModel.GetBuildingID(), m_wayPointModel.GetNextStepLevel());
                }
                DirectionsMenuInitiation::DirectionsMenuItemHighlightMessage message(m_wayPointModel.GetWpId());
                m_messageBus.Publish(message);
            }
        }
    }
}
