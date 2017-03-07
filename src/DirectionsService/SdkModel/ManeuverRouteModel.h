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
            class ManeuverRouteModel
            {
                
            public:
                
                ManeuverRouteModel(int bearing_after,int bearing_before,std::string type,Eegeo::Space::LatLong location);
                ~ManeuverRouteModel();
                
                const int GetBearingAfter() const;
                const int GetBearingBefore() const;
                const Eegeo::Space::LatLong& GetLocation() const;
                const std::string& GetType() const;
                
            private:
                
                int m_bearingAfter;
                int m_bearingBefore;
                std::string m_type;
                Eegeo::Space::LatLong m_location;
            };
        }
    }
}
