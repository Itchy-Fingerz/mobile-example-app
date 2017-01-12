// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "FindDirectionQuery.h"
#include "IWebLoadRequestFactory.h"
#include "FindDirectionHttpRequest.h"
#include "Route.h"


namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
        
            class FindDirectionHttpRequestFactory
            {
            public:
                FindDirectionHttpRequestFactory(const std::string& eeGeoApiKey,
                                                Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                const Eegeo::Routes::Webservice::RoutingRequestBuilder& requestBuilder
                                                );
                
                ~FindDirectionHttpRequestFactory();
                
                FindDirectionHttpRequest* CreateFindDirectionQuery(const FindDirectionQuery& query,
                                                           Eegeo::Helpers::ICallback0& completionCallback);
                
            private:
                const Eegeo::Routes::Webservice::RoutingRequestBuilder& m_requestBuilder;
                const std::string m_apiUrl;
                const std::string m_eegeoApiKey;
                Eegeo::Helpers::UrlHelpers::IUrlEncoder& m_urlEncoder;
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                
            };
        }
    }
}