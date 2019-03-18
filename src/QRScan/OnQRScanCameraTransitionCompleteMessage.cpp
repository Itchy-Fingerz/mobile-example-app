// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OnQRScanCameraTransitionCompleteMessage.h"

namespace ExampleApp
{
    namespace QRScan
    {
        OnQRScanCameraTransitionCompleteMessage::OnQRScanCameraTransitionCompleteMessage(bool isInterior)
        : m_isInterior(isInterior)
        {
        }
        
        bool OnQRScanCameraTransitionCompleteMessage::GetIsInterior() const
        {
            return m_isInterior;
        }
    }
}
