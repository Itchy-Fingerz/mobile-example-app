// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "StepRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {

            StepRouteModel::StepRouteModel(const int stepId,const ManeuverRouteModel maneuverRouteModel, const float distance,const float duration,const std::string mode,const std::string name, const std::string building_id,const bool inInterior,const int level)
            : m_stepId(stepId)
            , m_maneuverRouteModel(maneuverRouteModel)
            , m_distance(distance)
            , m_duration(duration)
            , m_mode(mode)
            , m_name(name)
            , m_building_id(building_id)
            , m_inInterior(inInterior)
            , m_level(level)
            {
            
            }
            StepRouteModel::~StepRouteModel()
            {
            
            }
                
            const ManeuverRouteModel& StepRouteModel::GetManeuverRouteModel() const
            {
                return m_maneuverRouteModel;
            }
            const float StepRouteModel::GetStepRouteDistance() const
            {
                
                return m_distance;
            }
            const float StepRouteModel::GetStepRouteDuration() const
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
            
            const std::string& StepRouteModel::GetBuildingID() const
            {
                return m_building_id;
            }
            
            const int StepRouteModel::GetStepID() const
            {
                return m_stepId;
            }
            
            const bool StepRouteModel::GetInInterior() const
            {
                return m_inInterior;
            }
            
            const int StepRouteModel::GetLevel() const
            {
                return m_level;
            }




        }
    }
}
