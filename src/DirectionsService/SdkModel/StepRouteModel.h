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
                StepRouteModel(const int stepId,const ManeuverRouteModel maneuverRouteModel, const float distance,const float duration,const std::string mode,const std::string name, const std::string building_id, const bool inInterior,const int level);
                ~StepRouteModel();
                
                const int GetStepID() const;
                const ManeuverRouteModel& GetManeuverRouteModel() const;
                const float GetStepRouteDistance() const;
                const float GetStepRouteDuration() const;
                const std::string& GetStepRouteMode() const;
                const std::string& GetStepRouteName() const;
                const std::string& GetBuildingID() const;
                const bool GetInInterior() const;
                const int GetLevel() const;




                
            private:
                
                int m_stepId;
                float m_distance;
                float m_duration;
                std::string m_mode;
                std::string m_name;
                std::string m_building_id;
                bool m_inInterior;
                ManeuverRouteModel m_maneuverRouteModel;
                int m_level;


                
                
                
            };
        }
    }
}
