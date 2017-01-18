// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "Types.h"
#include "space.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        class DirectionMenuFindDirectionMessage
        {
//          std::string m_searchQuery;
            
            const bool m_isInterior;
            const Eegeo::Space::LatLongAltitude &m_startLoc;
            const Eegeo::Space::LatLongAltitude &m_endLoc;
            const int m_startLocLevel;
            const int m_endLocLevel;
            
        public:
            
            DirectionMenuFindDirectionMessage(const Eegeo::Space::LatLongAltitude &startLocation, const Eegeo::Space::LatLongAltitude &endLocation,const int startLocLevel, const int endLocLevel ,const bool isInterior);
            //const std::string& SearchQuery() const;
            const Eegeo::Space::LatLongAltitude& StartLocation() const;
            const Eegeo::Space::LatLongAltitude& EndLocation() const;
            bool IsInterior() const;
            
            const int StartLocationLevel() const;
            const int EndLocationLevel() const;
        };
    }
}