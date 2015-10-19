// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Yelp.h"
#include "Search.h"
#include "Web.h"
#include "NetIncludes.h"
#include "UrlHelpers.h"
#include "ISearchServiceModule.h"
#include "AndroidNativeState.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class AndroidYelpSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
            {
            	Search::SdkModel::ISearchService* m_pSearchService;
                Yelp::SdkModel::IYelpSearchQueryFactory* m_pSearchQueryFactory;
                Search::SdkModel::ISearchResultParser* m_pSearchResultParser;
                Yelp::SdkModel::IYelpCategoryMapper* m_pYelpCategoryMapper;
                
            public:
                AndroidYelpSearchServiceModule(AndroidNativeState& nativeState,
                		Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                        Net::SdkModel::INetworkCapabilities& networkCapabilities,
                        Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder);
                
                ~AndroidYelpSearchServiceModule();
                
                Search::SdkModel::ISearchService& GetSearchService() const;
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
            };
        }
    }
}

