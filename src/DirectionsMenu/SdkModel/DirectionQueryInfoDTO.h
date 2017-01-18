// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include <string>

#include "Types.h"
#include "space.h"
#include "LatLongAltitude.h"



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
            
            public:
                DirectionQueryInfoDTO(const Eegeo::Space::LatLong startLoc,const Eegeo::Space::LatLong endLoc,const int startLocLevel,const int endLocLevel);
                ~DirectionQueryInfoDTO();
                
                const Eegeo::Space::LatLong StartLocation() const;
                const Eegeo::Space::LatLong EndLocation() const;
                const int StartLocationLevel() const;
                const int EndLocationLevel() const;
            };
        }
    }
}