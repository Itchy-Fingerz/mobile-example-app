// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ShowMeDirectionMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {

        ShowMeDirectionMessage::ShowMeDirectionMessage(Search::SdkModel::SearchResultModel searchResultModel)
        : m_searchResultModel(searchResultModel)
        {
        
        }
        ShowMeDirectionMessage::~ShowMeDirectionMessage()
        {
        
        }
        
        Search::SdkModel::SearchResultModel ShowMeDirectionMessage::GetSearchResultModel() const
        {
            return m_searchResultModel;
        }

        
    }
}
