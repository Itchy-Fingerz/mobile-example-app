// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchServiceBase.h"

#include "GeoNames.h"
#include "NetIncludes.h"
#include "SearchQuery.h"
#include "IEegeoSearchQuery.h"
#include "IEegeoParser.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class GeoNamesSearchService : public Search::SdkModel::SearchServiceBase, private Eegeo::NonCopyable
                {
                private:
                    IGeoNamesSearchQueryFactory& m_geoNamesSearchQueryFactory;
                    IGeoNamesParser& m_geoNamesParser;
                    Net::SdkModel::INetworkCapabilities& m_networkCapabilities;
                    Search::SdkModel::SearchQuery m_currentQueryModel;
                    Eegeo::Helpers::TCallback0<GeoNamesSearchService> m_searchCallback;
                    EegeoPois::SdkModel::IEegeoSearchQuery* m_pCurrentRequest;
                    bool m_hasActiveQuery;
                    EegeoPois::SdkModel::IEegeoParser& m_eegeoSearchParser;
                    
                public:
                    GeoNamesSearchService(IGeoNamesSearchQueryFactory& geoNamesSearchQueryFactory,
                                          IGeoNamesParser& geoNamesParser,
                                          Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                          EegeoPois::SdkModel::IEegeoParser& eegeoSearchParser);
                    
                    ~GeoNamesSearchService();
                    
                    void CancelInFlightQueries();
                    
                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                    
                private:
                    void HandleSearchResponse();
                };
            }
        }
    }
}