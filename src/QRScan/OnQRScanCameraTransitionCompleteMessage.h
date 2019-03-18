// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>

namespace ExampleApp
{
    namespace QRScan
    {
        class OnQRScanCameraTransitionCompleteMessage
        {
        private:
            bool m_isInterior;
        public:
            OnQRScanCameraTransitionCompleteMessage(bool isInterior);
            bool GetIsInterior() const;
        };
    }
}
