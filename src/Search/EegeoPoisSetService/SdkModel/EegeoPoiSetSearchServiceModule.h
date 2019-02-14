// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"
#include "EegeoPoiSetSearchService.h"

#include "Web.h"
#include "Search.h"
#include "ITagIconMapper.h"
#include "SearchTags.h"
#include <string>
#include "ApplicationDataSetConfig.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class EegeoPoiSetSearchServiceModule :  private Eegeo::NonCopyable
                {
                private:
                    IEegeoPoiSetSearchQueryFactory* m_pEegeoSearchQueryFactory;
                    IEegeoPoiSetParser* m_pEegeoParser;
                    IEegeoPoiSetSearchService* m_pSearchService;

                    TagSearch::SdkModel::ITagIconMapper* m_pTagIconMapper;
                    EegeoPoiSetReadableTagMapper* m_pReadableTagMapper;
                public:
                    EegeoPoiSetSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                   Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                   const Search::SdkModel::SearchTags& searchTags,
                                                   const std::string& serviceUrl,
                                                   const std::vector<ApplicationConfig::SdkModel::ApplicationDataSetConfig> appConfigSet);
                    
                    ~EegeoPoiSetSearchServiceModule();

                    IEegeoPoiSetSearchService& GetSearchService() const;
                };
            }
        }
    }
}
