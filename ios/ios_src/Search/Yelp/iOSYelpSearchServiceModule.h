// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Yelp.h"
#include "Search.h"
#include "GeoNames.h"
#include "Web.h"
#include "NetIncludes.h"
#include "UrlHelpers.h"
#include "ISearchServiceModule.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class iOSYelpSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
            {
                Search::SdkModel::ISearchService* m_pSearchService;
                SdkModel::IYelpSearchQueryFactory* m_pSearchQueryFactory;
                SdkModel::IYelpCategoryMapper* m_pYelpCategoryMapper;
                Search::SdkModel::ISearchResultParser* m_pSearchResultParser;
                
            public:
                iOSYelpSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                           Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                           Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder);
                
                ~iOSYelpSearchServiceModule();
                
                Search::SdkModel::ISearchService& GetSearchService() const;
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
            };
        }
    }
}

