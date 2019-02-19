// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanViewModel.h"

#include <sstream>
#include <iomanip>

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanViewModel::QRScanViewModel(
                Eegeo::Helpers::TIdentity identity)
                : m_openable(identity)
            {
                
            }

            QRScanViewModel::~QRScanViewModel()
            {
                
            }


            bool QRScanViewModel::IsOpen() const
            {
                return m_openable.IsOpen();
            }


            void QRScanViewModel::Open()
            {
                if(!IsOpen())
                {
                    m_openable.Open();
                    m_openedCallbacks.ExecuteCallbacks();
                }
            }

            void QRScanViewModel::Close()
            {
                if(IsOpen())
                {
                    m_openable.Close();
                    m_closedCallbacks.ExecuteCallbacks();
                }
            }
            
            OpenableControl::View::IOpenableControlViewModel& QRScanViewModel::GetOpenableControl()
            {
                return m_openable;
            }

            void QRScanViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void QRScanViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void QRScanViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void QRScanViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
            
        }
    }
}
