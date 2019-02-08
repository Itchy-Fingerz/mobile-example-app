// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "SearchServiceBase.h"
#include "IEegeoPoiSetSearchService.h"
#include "EegeoPoisSetService.h"
#include "NetIncludes.h"

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class EegeoPoiSetSearchService : public IEegeoPoiSetSearchService, private Eegeo::NonCopyable
                {
                private:
                    IEegeoPoiSetSearchQueryFactory& m_eeGeoSearchQueryFactory;
                    IEegeoPoiSetParser& m_eeGeoParser;
                    Net::SdkModel::INetworkCapabilities& m_networkCapabilities;
                    Eegeo::Helpers::TCallback0<EegeoPoiSetSearchService> m_searchCallback;
                    IEegeoPoiSetSearchQuery* m_pCurrentRequest;
                    bool m_hasActiveQuery;
                    Eegeo::Helpers::TCallback0<EegeoPoiSetSearchService> m_networkCapabilitiesChangedHandler;
                    Eegeo::Helpers::CallbackCollection2<const bool&, const std::vector<Search::SdkModel::SearchResultModel>& > m_queryResponseReceivedCallbacks;

                    
                public:
                    EegeoPoiSetSearchService(IEegeoPoiSetSearchQueryFactory& EegeoSearchQueryFactory,
                                           IEegeoPoiSetParser& EegeoParser,
                                           Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                           const std::vector<std::string>& handledTags);
                    
                    ~EegeoPoiSetSearchService();
                    
                    void CancelInFlightQueries();
                    
                    void PerformLocationSearchForDBInsertion();
                    
                    void InsertOnReceivedQueryResultsForLocalDBCallback(Eegeo::Helpers::ICallback2<const bool&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback);
                    
                    void RemoveOnReceivedQueryResultsForLocalDBCallback(Eegeo::Helpers::ICallback2<const bool&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback);
                                        
                private:
                    void HandleSearchResponse();
                    void HandleNetworkCapabilitiesChanged();
                };
            }
        }
    }
}
