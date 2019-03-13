// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "SearchServiceBase.h"
#include "NetIncludes.h"
#include "SearchQuery.h"
#include <vector>
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisLocalDB
        {
            namespace SdkModel
            {
                class EegeoPoisLocalDBSearchService : public Search::SdkModel::SearchServiceBase, private Eegeo::NonCopyable
                {
                private:
                    Net::SdkModel::INetworkCapabilities& m_networkCapabilities;
                    Search::SdkModel::SearchQuery m_currentQueryModel;
                    bool m_hasActiveQuery;
                    Eegeo::Helpers::TCallback0<EegeoPoisLocalDBSearchService> m_networkCapabilitiesChangedHandler;
                    PoiDb::SdkModel::PoiDbServiceProvider& m_dbServiceProvider;
                    
                public:
                    EegeoPoisLocalDBSearchService(Net::SdkModel::INetworkCapabilities& networkCapabilities,const std::vector<std::string>& handledTags,PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider);
                    
                    ~EegeoPoisLocalDBSearchService();
                    
                    bool CanHandleIndoor() const { return true; }

                    void CancelInFlightQueries();
                                        
                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                                        
                private:
                    void HandleNetworkCapabilitiesChanged();
                };
            }
        }
    }
}
