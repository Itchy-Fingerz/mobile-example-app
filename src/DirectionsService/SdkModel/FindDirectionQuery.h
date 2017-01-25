// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionQuery
            {
            private:
            
                Eegeo::Space::LatLongAltitude m_startLocation;
                Eegeo::Space::LatLongAltitude m_endLocation;
                bool m_isInterior;
                const int m_startLocLevel;
                const int m_endLocLevel;
                const std::string m_startBuildingID;
                const std::string m_endBuildingID;

            
            public:

                FindDirectionQuery(const Eegeo::Space::LatLongAltitude& startLocation,const int startLocLevel,const Eegeo::Space::LatLongAltitude& endLocation,const int endLocLevel,bool isInterior, std::string startBuuildingID, std::string endBuildingID);
                
                ~FindDirectionQuery();
                
                
                bool IsInterior() const;
                
                const Eegeo::Space::LatLongAltitude& StartLocation() const;
                
                const Eegeo::Space::LatLongAltitude& EndLocation() const;
                
                const int StartLocationLevel() const;
                
                const int EndLocationLevel() const;
                
                const std::string StartBuildingID() const;
                const std::string EndBuildingID() const;

            };
        }
    }
}