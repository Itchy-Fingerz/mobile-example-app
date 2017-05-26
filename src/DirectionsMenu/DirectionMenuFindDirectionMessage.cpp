// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "DirectionMenuFindDirectionMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        DirectionMenuFindDirectionMessage::DirectionMenuFindDirectionMessage(const Eegeo::Space::LatLongAltitude &startLocation, const Eegeo::Space::LatLongAltitude &endLocation, const int startLocLevel, const int endLocLevel, bool isInterior, std::string startBuuildingID, std::string endBuildingID):
         m_startLoc(startLocation)
        , m_endLoc(endLocation)
        , m_isInterior(isInterior)
        , m_startLocLevel(startLocLevel)
        , m_endLocLevel(endLocLevel)
        , m_startBuildingID(startBuuildingID)
        , m_endBuildingID(endBuildingID)
        {
            
        }
        
//        const std::string& DirectionMenuFindDirectionMessage::SearchQuery() const
//        {
//            return m_searchQuery;
//        }
        
        bool DirectionMenuFindDirectionMessage::IsInterior() const
        {
            return m_isInterior;
        }
        
        const Eegeo::Space::LatLongAltitude& DirectionMenuFindDirectionMessage::StartLocation() const
        {
            return m_startLoc;
        }
        
        const Eegeo::Space::LatLongAltitude& DirectionMenuFindDirectionMessage::EndLocation() const
        {
            return m_endLoc;
        }
        
        const int DirectionMenuFindDirectionMessage::StartLocationLevel() const
        {
            return m_startLocLevel;
        }
        
        const int DirectionMenuFindDirectionMessage::EndLocationLevel() const
        {
            return m_endLocLevel;
        }
        const std::string DirectionMenuFindDirectionMessage::StartBuildingID() const
        {
            return m_startBuildingID;
        }
        
        const std::string DirectionMenuFindDirectionMessage::EndBuildingID() const
        {
            return m_endBuildingID;
        }
        
    }
}