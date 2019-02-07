// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanIndoorPositionTypeMessage.h"

namespace ExampleApp
{
    namespace QRScan
    {
        QRScanIndoorPositionTypeMessage::QRScanIndoorPositionTypeMessage(std::string indoorPositioningType)
        : m_indoorPositioningType(std::move(indoorPositioningType))
        {
        }
        
        std::string QRScanIndoorPositionTypeMessage::GetIndoorPositioningType() const
        {
            return m_indoorPositioningType;
        }
    }
}
