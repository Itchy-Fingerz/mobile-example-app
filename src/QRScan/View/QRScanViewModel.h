// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IQRScanViewModel.h"
#include "CallbackCollection.h"
#include "QRScanOpenableControl.h"
#include "Reaction.h"
#include "QRScan.h"
#include <sstream>

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class QRScanViewModel : public IQRScanViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                QRScanOpenableControl m_openable;

                
            public:
                QRScanViewModel(
                    Eegeo::Helpers::TIdentity identity);

                ~QRScanViewModel();

                bool IsOpen() const;
                void Open();
                void Close();
                
                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl();

                void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
                void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
                            };
        }
    }
}
