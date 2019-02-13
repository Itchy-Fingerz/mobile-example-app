// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanViewInterop.h"
#include "QRScanView.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanViewInterop::QRScanViewInterop(QRScanView* pView) : m_pView(pView)
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
           
            void QRScanViewInterop::OnIndoorQRScanCompleted(double lat, double lng, const std::string& buildingId, int floorIndex, double orientation, double zoomLevel)
            {
            
                std::map<std::string, double> positionMap;
                positionMap["latitude"] = lat;
                positionMap["longitude"] = lng;
                positionMap["orientation"] = orientation;
                positionMap["zoom_level"] = zoomLevel;
                
                m_indoorQrScanCompletedCallbacks.ExecuteCallbacks(buildingId, floorIndex, positionMap);
            }
            
            void QRScanViewInterop::OnOutdoorQRScanCompleted(double lat, double lng, double orientation, double zoomLevel)
            {
                std::map<std::string, double> positionMap;
                positionMap["latitude"] = lat;
                positionMap["longitude"] = lng;
                positionMap["orientation"] = orientation;
                positionMap["zoom_level"] = zoomLevel;
                
                m_outdoorQrScanCompletedCallbacks.ExecuteCallbacks(positionMap);
            }

            void QRScanViewInterop::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void QRScanViewInterop::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
            
            void QRScanViewInterop::InsertOnIndoorQRScanCompletedCallback(Eegeo::Helpers::ICallback3<const std::string&, const int&, const std::map<std::string, double>&>& callback)
            {
                m_indoorQrScanCompletedCallbacks.AddCallback(callback);
            }

            void QRScanViewInterop::RemoveOnIndoorQRScanCompletedCallback(Eegeo::Helpers::ICallback3<const std::string&, const int&, const std::map<std::string, double>&>& callback)
            {
                m_indoorQrScanCompletedCallbacks.RemoveCallback(callback);
            }
            
            void QRScanViewInterop::InsertOnOutdoorQRScanCompletedCallback(Eegeo::Helpers::ICallback1<const std::map<std::string, double>&>& callback)
            {
                m_outdoorQrScanCompletedCallbacks.AddCallback(callback);
            }
            
            void QRScanViewInterop::RemoveOnOutdoorQRScanCompletedCallback(Eegeo::Helpers::ICallback1<const std::map<std::string, double>&>& callback)
            {
                m_outdoorQrScanCompletedCallbacks.RemoveCallback(callback);
            }
            
        }
    }
}
