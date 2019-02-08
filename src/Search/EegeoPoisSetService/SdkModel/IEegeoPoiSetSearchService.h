// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class IEegeoPoiSetSearchService
                {
                public:
                    
                    virtual void PerformLocationSearchForDBInsertion() = 0;

                    virtual ~IEegeoPoiSetSearchService() { }
                    
                    virtual void InsertOnReceivedQueryResultsForLocalDBCallback(Eegeo::Helpers::ICallback2<const bool&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback) = 0;
                    
                    virtual void RemoveOnReceivedQueryResultsForLocalDBCallback(Eegeo::Helpers::ICallback2<const bool&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback) = 0;
                    
                };
            }
        }
    }
}
