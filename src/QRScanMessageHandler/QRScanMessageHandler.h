// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "IPopUpViewModel.h"
#include "OnQRScanCameraTransitionCompleteMessage.h"
#include "CurrentLocationService.h"
#include "InteriorsCameraController.h"
#include "GlobeCameraController.h"
#include "BlueSphereModel.h"

namespace ExampleApp
{
    namespace QRScanMessageHandler
    {
        class QRScanMessageHandler
        {
        private:
            
            ExampleAppMessaging::TMessageBus& m_messageBus;
            
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const QRScan::OnQRScanCameraTransitionCompleteMessage&> m_qrScanCameraTransitionCompleted;
            
            Eegeo::Helpers::CurrentLocationService::CurrentLocationService& m_currentLocationService;
            Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
            Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
            
            Eegeo::BlueSphere::BlueSphereModel& m_blueSphereModel;
            ExampleApp::PopUp::View::IPopUpViewModel& m_popUpViewModel;
            
            void OnQRScanCameraTransitionCompleted(const QRScan::OnQRScanCameraTransitionCompleteMessage& message);

        public:
            QRScanMessageHandler(Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                 Eegeo::Resources::Interiors::InteriorsCameraController& interiorCameraController,
                                 Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                 ExampleApp::PopUp::View::IPopUpViewModel& popUpViewModel,
                                 Eegeo::BlueSphere::BlueSphereModel& blueSphereModel,
                                 ExampleAppMessaging::TMessageBus& messageBus);
            ~QRScanMessageHandler();
            
        };
    }
}
