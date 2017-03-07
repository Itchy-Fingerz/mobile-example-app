// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionInnerRouteModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            
            DirectionInnerRouteModel::DirectionInnerRouteModel(int duration,int distance ,const DirectionRouteGeometryModel& pGeometry, std::vector<LegRouteModel>legs)
            : m_duration(duration)
            , m_distance(distance)
            , m_Geometry(pGeometry)
            , m_legs(legs)
            {
            
            }
            
            DirectionInnerRouteModel::~DirectionInnerRouteModel()
            {
            
            }
            
            const int DirectionInnerRouteModel::GetDuration() const
            {
                return m_duration;
            }
            
            const float DirectionInnerRouteModel::GetDistance() const
            {
                return m_distance;
            }
            
            const DirectionRouteGeometryModel& DirectionInnerRouteModel::GetInnerRouteGeometry() const
            {
                return m_Geometry;
            }
            
            const std::vector<LegRouteModel>& DirectionInnerRouteModel::GetInnerRouteLegs() const
            {
                return m_legs;
            }

        }
    }
}