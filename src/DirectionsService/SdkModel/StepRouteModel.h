// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ManeuverRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class StepRouteModel
            {
            public:
                StepRouteModel(ManeuverRouteModel maneuverRouteModel, float distance,float duration,std::string mode,std::string name);
                ~StepRouteModel();
                
                const ManeuverRouteModel& GetManeuverRouteModel() const;
                const float& GetStepRouteDistance() const;
                const float& GetStepRouteDuration() const;
                const std::string& GetStepRouteMode() const;
                const std::string& GetStepRouteName() const;


                
            private:
                
                ManeuverRouteModel m_maneuverRouteModel;
                float m_distance;
                float m_duration;
                std::string m_mode;
                std::string m_name;
                
                
                
            };
        }
    }
}
