// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IGeoNamesSearchQueryFactory.h"
#include "IGeoNamesSearchQuery.h"
#include "Web.h"
#include "UrlHelpers.h"
#include "Interiors.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class GeoNamesSearchQueryFactory : public IGeoNamesSearchQueryFactory, private Eegeo::NonCopyable
                {
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                    Eegeo::Helpers::UrlHelpers::IUrlEncoder& m_urlEncoder;
                    const Eegeo::Web::ApiTokenModel& m_apiTokenModel;
                    
                    std::string m_geoNamesUserName;
                    const std::string m_serviceUrl;



                    
                public:
                    GeoNamesSearchQueryFactory(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                               Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                               const std::string& serviceUrl,
                                               const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                               const std::string& geoNamesUserName);
                    
                    ~GeoNamesSearchQueryFactory();
                    
                    EegeoPois::SdkModel::IEegeoSearchQuery* CreateGeoNamesSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                       Eegeo::Helpers::ICallback0& completionCallback);
                };
            }
        }
    }
}
