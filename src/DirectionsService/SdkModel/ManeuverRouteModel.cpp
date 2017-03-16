// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ManeuverRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            ManeuverRouteModel::ManeuverRouteModel(int bearing_after,int bearing_before,std::string type,Eegeo::Space::LatLong location,std::string modifier)
            : m_bearingAfter(bearing_after)
            , m_bearingBefore(bearing_before)
            , m_type(type)
            , m_location(location)
            , m_modifier(modifier)
            {
            
            }
            
            ManeuverRouteModel::~ManeuverRouteModel()
            {
            
            }
            
            const int ManeuverRouteModel::GetBearingAfter() const
            {
                return m_bearingAfter;
            }
            
            const int ManeuverRouteModel::GetBearingBefore() const
            {
                return m_bearingBefore;
            }
            
            const Eegeo::Space::LatLong& ManeuverRouteModel::GetLocation() const
            {
                return m_location;
            }
            
            const std::string& ManeuverRouteModel::GetType() const
            {
                return m_type;
            }
            
            const std::string& ManeuverRouteModel::GetModifier() const
            {
                return m_modifier;
            }

            
        }
    }
}
