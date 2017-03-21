// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointModel.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        
        WayPointModel::WayPointModel(const int wpId
                                     , const ExampleApp::PathDrawing::WayPointType::Values type
                                     , Eegeo::Space::LatLong& location
                                     , const std::string title
                                     , const std::string buildingID
                                     , const int level
                                     , const bool inInterior
                                     , const bool isWayPoint)
        : m_id(wpId)
        , m_type(type)
        , m_location(location)
        , m_title(title)
        , m_level(level)
        , m_buildingID(buildingID)
        , m_inInterior(inInterior)
        , m_isWaypoint(isWayPoint)
        {
        }
        
        const int WayPointModel::GetWpId()
        {
            return m_id;
        }

        const std::string WayPointModel::GetTitle()
        {
            return m_title;
        }
        
        const ExampleApp::PathDrawing::WayPointType::Values WayPointModel::GetType()
        {
            return m_type;
        }
        
        const Eegeo::Space::LatLong& WayPointModel::GetLocation()
        {
            return m_location;
        }
        
        const int WayPointModel::GetLevel()
        {
            return m_level;
        }
        
        const std::string WayPointModel::GetBuildingID()
        {
            return m_buildingID;
        }
        
        const bool WayPointModel::GetInInterior()
        {
            return m_inInterior;
        }
        
        const bool WayPointModel::GetIsWayPoint()
        {
            return m_isWaypoint;
        }

    }

}
