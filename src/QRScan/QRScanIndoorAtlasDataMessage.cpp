// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanSenionDataMessage.h"
#include "QRScanIndoorAtlasDataMessage.h"

namespace ExampleApp
{
    namespace QRScan
    {
        QRScanIndoorAtlasDataMessage::QRScanIndoorAtlasDataMessage(int eeegeoFloorIndex,
                                                                         std::string indoorAtlasFloorId,
                                                                         double latitude,
                                                                         double longitude)
        : m_eegeoFloorIndex(eeegeoFloorIndex)
        , m_indoorAtlasFloorId(indoorAtlasFloorId)
        , m_latitude(latitude)
        , m_longitude(longitude)
        {
        }
        
        int32_t QRScanIndoorAtlasDataMessage::GetEegeoFloorIndex() const
        {
            return m_eegeoFloorIndex;
        }
        
        std::string QRScanIndoorAtlasDataMessage::GetIndoorAtlasFloorId() const
        {
            return m_indoorAtlasFloorId;
        }
        
        double QRScanIndoorAtlasDataMessage::GetLatitude() const
        {
            return m_latitude;
        }
        
        double QRScanIndoorAtlasDataMessage::GetLongitude()const
        {
            return m_longitude;
        }
    }
}
