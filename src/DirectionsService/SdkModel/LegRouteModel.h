// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "StepRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class LegRouteModel
            {
            public:
                LegRouteModel(float distance, float duration, std::vector<StepRouteModel> steps, std::string summary);
                ~LegRouteModel();
                
                const float& GetLegRouteDistance() const;
                const float& GetLegRouteDuration() const;
                const std::vector<StepRouteModel>& GetLegRouteSteps() const;
                const std::string& GetLegRouteSummary() const;

            private:
                
                float m_distance;
                float m_duration;
                std::vector<StepRouteModel> m_steps;
                std::string m_summary;
                
            };
        }
    }
}