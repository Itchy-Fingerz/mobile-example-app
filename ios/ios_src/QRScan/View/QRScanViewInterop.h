// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "QRScanViewIncludes.h"
#include "IQRScanView.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class QRScanViewInterop : public IQRScanView, private Eegeo::NonCopyable
            {
            private:
                QRScanView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;
                Eegeo::Helpers::CallbackCollection3<const std::string&, const int&, const std::map<std::string, double>&> m_indoorQrScanCompletedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const std::map<std::string, double>&> m_outdoorQrScanCompletedCallbacks;
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                QRScanViewInterop(ExampleAppMessaging::TMessageBus& messageBus, QRScanView* pView);

                void CloseTapped();

                void Open();

                void Close();

                virtual void OnIndoorQRScanCompleted(double lat, double lng, const std::string& buildingId, int floorIndex, double orientation, double zoomLevel, double tiltInDegree);
               
                virtual void OnOutdoorQRScanCompleted(double lat, double lng, double orientation, double zoomLevel, double tiltInDegree);

                void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);
                
            };
        }
    }

}
