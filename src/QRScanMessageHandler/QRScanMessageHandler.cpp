// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanMessageHandler.h"
#include "MarkerBuilder.h"
#include "CameraHelpers.h"
#include "BlueSphereModel.h"

namespace ExampleApp
{
    namespace QRScanMessageHandler
    {

        QRScanMessageHandler::QRScanMessageHandler(Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                   Eegeo::Resources::Interiors::InteriorsCameraController& interiorCameraController,
                                                   Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                                   ExampleApp::PopUp::View::IPopUpViewModel& popUpViewModel,
                                                   Eegeo::BlueSphere::BlueSphereModel& blueSphereModel,
                                                   ExampleAppMessaging::TMessageBus& messageBus)
        : m_currentLocationService(currentLocationService)
        , m_interiorsCameraController(interiorCameraController)
        , m_globeCameraController(globeCameraController)
        , m_popUpViewModel(popUpViewModel)
        , m_blueSphereModel(blueSphereModel)
        , m_messageBus(messageBus)
        , m_qrScanCameraTransitionCompleted(this, &QRScanMessageHandler::OnQRScanCameraTransitionCompleted)
        {
            m_messageBus.SubscribeUi(m_qrScanCameraTransitionCompleted);
        }
        
        QRScanMessageHandler::~QRScanMessageHandler()
        {
            m_messageBus.UnsubscribeUi(m_qrScanCameraTransitionCompleted);
        }
        
        void QRScanMessageHandler::OnQRScanCameraTransitionCompleted(const ExampleApp::QRScan::OnQRScanCameraTransitionCompleteMessage &message)
        {

            Eegeo::Space::LatLong currentLatLong(0.0, 0.0);
            m_currentLocationService.GetLocation(currentLatLong);
            double currentAlt = m_blueSphereModel.GetSphereHeightAboveBase();
            Eegeo::Space::LatLongAltitude currentLatLongAlt(currentLatLong.GetLatitude(),currentLatLong.GetLongitude(),currentAlt);
            if(message.GetIsInterior())
            {
                Eegeo::v3 screenPosition = Eegeo::Camera::CameraHelpers::GetScreenPositionFromLatLongAlt(currentLatLongAlt, m_interiorsCameraController.GetRenderCamera());
                m_popUpViewModel.Open(screenPosition.GetX(), screenPosition.GetY());
            }
            else
            {
                Eegeo::v3 screenPosition = Eegeo::Camera::CameraHelpers::GetScreenPositionFromLatLongAlt(currentLatLongAlt, m_globeCameraController.GetRenderCamera());
                m_popUpViewModel.Open(screenPosition.GetX(), screenPosition.GetY());
            }
            
            
        }
        
    }
}
