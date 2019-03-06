// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IQRScanView.h"
#include "AndroidNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class QRScanView : public IQRScanView, private Eegeo::NonCopyable
            {
            private:
                AndroidNativeState& m_nativeState;
                jclass m_uiViewClass;
                jobject m_uiView;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;

            public:
                QRScanView(AndroidNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus);

                ~QRScanView();

                void CloseTapped();

                void Open();

                void Close();

                void OnIndoorQRScanCompleted(double lat, double lng, const std::string& buildingId, int floorIndex, double orientation, double zoomLevel, double tiltAngle);

                void OnOutdoorQRScanCompleted(double lat, double lng, double orientation, double zoomLevel, double tiltAngle);

                void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

            };
        }
    }
}
