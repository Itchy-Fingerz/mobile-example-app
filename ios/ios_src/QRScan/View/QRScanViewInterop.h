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
                Eegeo::Helpers::CallbackCollection0 m_hiddenTextCallbacks;

            public:
                QRScanViewInterop(QRScanView* pView);

                void CloseTapped();

                void Open();

                void Close();

                void SetContent(const std::string& content);
                
                void ShowHiddenText();

                void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback);
                
                void RemoveLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }

}
