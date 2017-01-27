// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "DirectionMenuPoiSearchResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        DirectionMenuPoiSearchResponseReceivedMessage::DirectionMenuPoiSearchResponseReceivedMessage(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& results, bool   isStartLocationActive):
            m_searchResults(results)
        , m_isForStartLocation(isStartLocationActive)
        {
            
        }
        
        const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& DirectionMenuPoiSearchResponseReceivedMessage::SearchResults() const
        {
            return m_searchResults;
        }
        
        bool DirectionMenuPoiSearchResponseReceivedMessage::IsForStartLocation() const
        {
            return m_isForStartLocation;
        }
        
    }
}
