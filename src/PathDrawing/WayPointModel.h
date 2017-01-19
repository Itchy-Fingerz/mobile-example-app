// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "WayPointType.h"
#include "space.h"
#include <string>
#include "LatLongAltitude.h"
namespace ExampleApp
{
    namespace PathDrawing
    {
        class WayPointModel
        {
        private:
            const int m_id;
            const std::string m_title;
            const ExampleApp::PathDrawing::WayPointType::Values m_type;
            const std::string m_buildingID;
            bool m_inInterior;
            const int m_level;
            const Eegeo::Space::LatLong m_location;
       
        public:
            WayPointModel(const int wpId
                     , const ExampleApp::PathDrawing::WayPointType::Values type
                     , Eegeo::Space::LatLong& location
                          , const std::string title, const std::string buildingID, const int level, const bool inInterior);
            
            const int GetWpId();
            const std::string GetTitle();
            const ExampleApp::PathDrawing::WayPointType::Values GetType();
            const Eegeo::Space::LatLong& GetLocation();
            const int GetLevel();
            const std::string GetBuildingID();
            const bool GetInInterior();
            
            virtual ~WayPointModel() { }
        };
        
    }
}
