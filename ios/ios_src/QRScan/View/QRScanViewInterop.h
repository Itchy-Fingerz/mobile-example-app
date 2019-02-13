// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "QRScanViewIncludes.h"
#include "IQRScanView.h"
#include "ICallback.h"
#include "CallbackCollection.h"

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
                Eegeo::Helpers::CallbackCollection3<const std::string&, const std::string&,
                            const std::map<std::string, double>&> m_qrScanCompletedCallbacks;

            public:
                QRScanViewInterop(QRScanView* pView);

                void CloseTapped();

                void Open();

                void Close();

                void OnQRScanCompleted(const std::string& host, double lat, double lng, const std::string& buildingId, double orientation);

                void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertOnQRScanCompletedCallback(Eegeo::Helpers::ICallback3<const std::string&, const std::string&, const std::map<std::string, double>&>& callback);
                
                void RemoveOnQRScanCompletedCallback(Eegeo::Helpers::ICallback3<const std::string&, const std::string&, const std::map<std::string, double>&>& callback);
                


            };
        }
    }

}
