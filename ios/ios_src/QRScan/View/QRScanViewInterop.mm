// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanViewInterop.h"
#include "QRScanView.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanViewInterop::QRScanViewInterop(ExampleAppMessaging::TMessageBus& messageBus, QRScanView* pView)
            : m_pView(pView)
            , m_messageBus(messageBus)
            {

            }

            void QRScanViewInterop::CloseTapped()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void QRScanViewInterop::Open()
            {
                [m_pView setFullyActive];
            }

            void QRScanViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }
           
            void QRScanViewInterop::OnIndoorQRScanCompleted(double lat, double lng, const std::string& buildingId, int floorIndex, double orientation, double zoomLevel, double tiltInDegree)
            {
                m_messageBus.Publish(QRScan::OnIndoorQRScanCompleteMessage(
                                                                           lat,
                                                                           lng,
                                                                           buildingId,
                                                                           floorIndex,
                                                                           orientation,
                                                                           zoomLevel,
                                                                           tiltInDegree));
            }
            
            void QRScanViewInterop::OnOutdoorQRScanCompleted(double lat, double lng, double orientation, double zoomLevel, double tiltInDegree)
            {
                m_messageBus.Publish(QRScan::OnOutdoorQRScanCompleteMessage(
                                                                            lat,
                                                                            lng,
                                                                            orientation,
                                                                            zoomLevel,
                                                                            tiltInDegree));
            }

            void QRScanViewInterop::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void QRScanViewInterop::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
            
   
        }
    }
}
