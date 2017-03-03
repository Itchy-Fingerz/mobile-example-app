// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LegRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {

            LegRouteModel::LegRouteModel(float distance, float duration, std::vector<StepRouteModel> steps, std::string summary)
            : m_distance(distance)
            , m_duration(duration)
            , m_steps(steps)
            , m_summary(summary)
            {
            
            }
            LegRouteModel::~LegRouteModel()
            {
            
            }
                
            const float& LegRouteModel::GetLegRouteDistance() const
            {
                return m_distance;
            }
            
            const float& LegRouteModel::GetLegRouteDuration() const
            {
                return m_duration;
            }
            
            const std::vector<StepRouteModel>& LegRouteModel::GetLegRouteSteps() const
            {
                return m_steps;
            }
            
            const std::string& LegRouteModel::GetLegRouteSummary() const
            {
                return m_summary;
            }
        }
    }
}
