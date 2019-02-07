// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanSenionDataMessage.h"

namespace ExampleApp
{
    namespace QRScan
    {
        QRScanSenionDataMessage::QRScanSenionDataMessage(int eeegeoFloorNumber, int32_t senionFloorNumber, double senionLatitude, double senionLongitude)
        : m_eegeoFloorNumber(eeegeoFloorNumber)
        , m_senionFloorNumber(senionFloorNumber)
        , m_sentionLatitude(senionLatitude)
        , m_senionLongitude(senionLongitude)
        {
        }
        
        int32_t QRScanSenionDataMessage::GetEegeoFloorNumber() const
        {
            return m_eegeoFloorNumber;
        }
        
        int QRScanSenionDataMessage::GetSenionFloorNumber() const
        {
            return m_senionFloorNumber;
        }
        
        double QRScanSenionDataMessage::GetSenionLatitude() const
        {
            return m_sentionLatitude;
        }
        
        double QRScanSenionDataMessage::GetSenionLongitude()const
        {
            return m_senionLongitude;
        }
    }
}
