// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include <string>

#include "Types.h"
#include "space.h"
#include "LatLongAltitude.h"
#include "string.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            class DirectionQueryInfoDTO
            {
                const Eegeo::Space::LatLong m_startLoc;
                const Eegeo::Space::LatLong m_endLoc;
                const int m_startLocLevel;
                const int m_endLocLevel;
                const std::string m_startBuildingID;
                const std::string m_endBuildingID;
            
            public:
                DirectionQueryInfoDTO(const Eegeo::Space::LatLong startLoc,const Eegeo::Space::LatLong endLoc,const int startLocLevel,const int endLocLevel, std::string startBuuildingID, std::string endBuildingID);
                ~DirectionQueryInfoDTO();
                
                const Eegeo::Space::LatLong StartLocation() const;
                const Eegeo::Space::LatLong EndLocation() const;
                const int StartLocationLevel() const;
                const int EndLocationLevel() const;
                
                const std::string StartBuildingID() const;
                const std::string EndBuildingID() const;
            };
        }
    }
}