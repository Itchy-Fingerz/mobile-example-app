// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionQueryInfoDTO.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            DirectionQueryInfoDTO::DirectionQueryInfoDTO(const Eegeo::Space::LatLong startLoc,const Eegeo::Space::LatLong endLoc,const int startLocLevel,const int endLocLevel)
            : m_startLoc(startLoc)
            , m_endLoc(endLoc)
            , m_startLocLevel(startLocLevel)
            , m_endLocLevel(endLocLevel)
            {
            
            }
            
            DirectionQueryInfoDTO::~DirectionQueryInfoDTO()
            {
                
            }

            const Eegeo::Space::LatLong DirectionQueryInfoDTO::StartLocation() const
            {
                return m_startLoc;
            }
            
            const Eegeo::Space::LatLong DirectionQueryInfoDTO::EndLocation() const
            {
                return m_endLoc;
            }
            
            const int DirectionQueryInfoDTO::StartLocationLevel() const
            {
                return m_startLocLevel;
            }
            
            const int DirectionQueryInfoDTO::EndLocationLevel() const
            {
                return m_endLocLevel;
            }
            
        }
    }
}