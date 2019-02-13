// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanIndoorPositionSettingsMessage.h"

namespace ExampleApp
{
    namespace QRScan
    {
        QRScanIndoorPositionSettingsMessage::QRScanIndoorPositionSettingsMessage(std::string apiKey, std::string apiSecret, std::map<int, std::string> floorMap, std::string interiorId)
        : m_apiKey(apiKey)
        , m_apiSecret(apiSecret)
        , m_floorMap(floorMap)
        , m_interiorId(interiorId)
        {
        }
        
        std::string QRScanIndoorPositionSettingsMessage::GetApiKey() const
        {
            return m_apiKey;
        }
        
        std::string QRScanIndoorPositionSettingsMessage::GetApiSecret() const
        {
            return m_apiSecret;
        }
        
        std::map<int, std::string> QRScanIndoorPositionSettingsMessage::GetFloorMap() const
        {
            return m_floorMap;
        }
        
        std::string QRScanIndoorPositionSettingsMessage::GetInteriorId() const
        {
            return m_interiorId;
        }
    }
}
