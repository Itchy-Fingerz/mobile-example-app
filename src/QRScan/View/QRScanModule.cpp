// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanModule.h"
#include "QRScanViewModel.h"
#include "EegeoWorld.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanModule::QRScanModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                             const std::string& buildVersion,
                                             const std::string& appName)
            {
                std::string platformRuntimeArchitecture = (sizeof(void*) == 4) ? "32-bit" : "64-bit";
                m_pQRScanViewModel = Eegeo_NEW(QRScanViewModel)(identityProvider.GetNextIdentity(), buildVersion, EEGEO_PLATFORM_VERSION_NUMBER, EEGEO_PLATFORM_VERSION_HASH, platformRuntimeArchitecture, "", appName);
            }

            QRScanModule::~QRScanModule()
            {
                Eegeo_DELETE m_pQRScanViewModel;
            }

            IQRScanViewModel& QRScanModule::GetQRScanViewModel() const
            {
                return *m_pQRScanViewModel;
            }

            OpenableControl::View::IOpenableControlViewModel& QRScanModule::GetObservableOpenableControl() const
            {
                return m_pQRScanViewModel->GetOpenableControl();
            }
        }
    }
}
