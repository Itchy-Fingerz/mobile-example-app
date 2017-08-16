// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultSectionOrder.h"
#include <string>

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            class DirectionsResultsOrder : public SearchResultSection::View::ISearchResultSectionOrder
            {
                std::string m_queryString;
                
            public:
                bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b);
                
                void SetQueryString(std::string queryString)
                {
                    m_queryString = queryString;
                }
            };
        }
    }
}
