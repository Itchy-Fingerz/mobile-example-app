// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanOpenableControl.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanOpenableControl::QRScanOpenableControl(Eegeo::Helpers::TIdentity identity)
                : OpenableControl::View::OpenableControlViewModelBase()
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity QRScanOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
