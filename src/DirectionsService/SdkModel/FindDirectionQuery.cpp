// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FindDirectionQuery.h"


namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            
            FindDirectionQuery::FindDirectionQuery(const Eegeo::Space::LatLongAltitude& startLocation,const int startLocLevel,const Eegeo::Space::LatLongAltitude& endLocation,const int endLocLevel,bool isInterior, std::string startBuuildingID, std::string endBuildingID)
            : m_startLocation(startLocation)
            , m_endLocation(endLocation)
            , m_isInterior(isInterior)
            , m_startLocLevel(startLocLevel)
            , m_endLocLevel(endLocLevel)
            , m_startBuildingID(startBuuildingID)
            , m_endBuildingID(endBuildingID)
            {
            
            }
            
            FindDirectionQuery::~FindDirectionQuery()
            {
            
            }
            
            bool FindDirectionQuery::IsInterior() const
            {
                return m_isInterior;
            }
            
            const Eegeo::Space::LatLongAltitude& FindDirectionQuery::StartLocation() const
            {
                return m_startLocation;
            }
            
            const Eegeo::Space::LatLongAltitude& FindDirectionQuery::EndLocation() const
            {
                return m_endLocation;
            }

            const int FindDirectionQuery::StartLocationLevel() const
            {
                if(m_startBuildingID == "98a265e2-b890-4c6b-a28f-948c92e36914")
                {
                    return m_startLocLevel + 2;
                }
                return m_startLocLevel;
            }
            
            const int FindDirectionQuery::EndLocationLevel() const
            {
                if(m_startBuildingID == "98a265e2-b890-4c6b-a28f-948c92e36914")
                {
                    return m_endLocLevel + 2;
                }
                return m_endLocLevel;
            }

            const std::string FindDirectionQuery::StartBuildingID() const
            {
                return m_startBuildingID;
            }
            
            const std::string FindDirectionQuery::EndBuildingID() const
            {
                return m_endBuildingID;
            }
            

        }
    }
}





