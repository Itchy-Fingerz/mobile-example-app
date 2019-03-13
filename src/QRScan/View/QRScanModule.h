// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "QRScan.h"
#include "IQRScanModule.h"
#include "QRScanViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class QRScanModule : public IQRScanModule, private Eegeo::NonCopyable
            {
                QRScanViewModel* m_pQRScanViewModel;

            public:
                QRScanModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                const std::string& buildVersion,
                                const std::string& appName);

                ~QRScanModule();

                IQRScanViewModel& GetQRScanViewModel() const;

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
            };
        }
    }
}
