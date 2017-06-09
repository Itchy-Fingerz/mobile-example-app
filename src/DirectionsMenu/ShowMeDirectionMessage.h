// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        class ShowMeDirectionMessage
        {
        public:
            ShowMeDirectionMessage(Search::SdkModel::SearchResultModel searchResultModel);
            ~ShowMeDirectionMessage();
            
            Search::SdkModel::SearchResultModel GetSearchResultModel() const;
            
        private:
            Search::SdkModel::SearchResultModel m_searchResultModel;
        };
    }
}
