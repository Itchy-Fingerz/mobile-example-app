// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "StepRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {

            StepRouteModel::StepRouteModel(ManeuverRouteModel maneuverRouteModel, float distance,float duration,std::string mode,std::string name)
            : m_maneuverRouteModel(maneuverRouteModel)
            , m_distance(distance)
            , m_duration(duration)
            , m_mode(mode)
            , m_name(name)
            {
            
            }
            StepRouteModel::~StepRouteModel()
            {
            
            }
                
            const ManeuverRouteModel& StepRouteModel::GetManeuverRouteModel() const
            {
                return m_maneuverRouteModel;
            }
            const float& StepRouteModel::GetStepRouteDistance() const
            {
                return m_distance;
            }
            const float& StepRouteModel::GetStepRouteDuration() const
            {
                return m_duration;
            }
            const std::string& StepRouteModel::GetStepRouteMode() const
            {
                return m_mode;
            }
            const std::string& StepRouteModel::GetStepRouteName() const
            {
                return m_name;
            }
        }
    }
}