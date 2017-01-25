// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionQueryInfoDTO.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            DirectionQueryInfoDTO::DirectionQueryInfoDTO(const Eegeo::Space::LatLong startLoc,const Eegeo::Space::LatLong endLoc,const int startLocLevel,const int endLocLevel,std::string startBuuildingID, std::string endBuildingID)
            : m_startLoc(startLoc)
            , m_endLoc(endLoc)
            , m_startLocLevel(startLocLevel)
            , m_endLocLevel(endLocLevel)
            , m_startBuildingID(startBuuildingID)
            , m_endBuildingID(endBuildingID)
            {
            
            }
            
            DirectionQueryInfoDTO::~DirectionQueryInfoDTO()
            {
                
            }

            const Eegeo::Space::LatLong DirectionQueryInfoDTO::StartLocation() const
            {
                return m_startLoc;
            }
            
            const Eegeo::Space::LatLong DirectionQueryInfoDTO::EndLocation() const
            {
                return m_endLoc;
            }
            
            const int DirectionQueryInfoDTO::StartLocationLevel() const
            {
                return m_startLocLevel;
            }
            
            const int DirectionQueryInfoDTO::EndLocationLevel() const
            {
                return m_endLocLevel;
            }
            
            const std::string DirectionQueryInfoDTO::StartBuildingID() const
            {
                return m_startBuildingID;
            }
            
            const std::string DirectionQueryInfoDTO::EndBuildingID() const
            {
                return m_endBuildingID;
            }
            
            
        }
    }
}