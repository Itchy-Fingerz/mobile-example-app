// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace QRScan
    {
        class QRScanIndoorPositionTypeMessage
        {
            std::string m_indoorPositioningType;
            
        public:
            QRScanIndoorPositionTypeMessage(std::string indoorPositioningType);
            
            std::string GetIndoorPositioningType() const;
        };
    }
}
