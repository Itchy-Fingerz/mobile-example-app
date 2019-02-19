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
                m_pQRScanViewModel = Eegeo_NEW(QRScanViewModel)(identityProvider.GetNextIdentity());
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
