// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "LegRouteModel.h"
#include "DirectionRouteGeometryModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class DirectionInnerRouteModel
            {
            public:
                
                DirectionInnerRouteModel(int duration,int distance  , const DirectionRouteGeometryModel& pGeometry, std::vector<LegRouteModel>legs);
                ~DirectionInnerRouteModel();
                const int GetDuration() const;
                const float GetDistance() const;
                const DirectionRouteGeometryModel& GetInnerRouteGeometry() const;
                const std::vector<LegRouteModel>& GetInnerRouteLegs() const;
                
            private:
                
                int m_duration;
                float m_distance;
                DirectionRouteGeometryModel m_Geometry;
                std::vector<LegRouteModel> m_legs;
                
            };
        
        }
    }
}