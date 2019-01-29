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

            void QRScanViewInterop::SetContent(const std::string& content)
            {
                [m_pView setContent:&content];
            }
            
            void QRScanViewInterop::ShowHiddenText()
            {
                m_hiddenTextCallbacks.ExecuteCallbacks();
            }

            void QRScanViewInterop::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void QRScanViewInterop::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
            
            void QRScanViewInterop::InsertLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_hiddenTextCallbacks.AddCallback(callback);
            }
            
            void QRScanViewInterop::RemoveLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_hiddenTextCallbacks.RemoveCallback(callback);
            }
        }
    }
}
