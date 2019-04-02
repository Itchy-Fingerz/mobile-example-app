// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IEegeoPoiSetSearchQueryFactory.h"
#include "IEegeoPoiSetSearchQuery.h"
#include "Web.h"
#include "UrlHelpers.h"
#include "Interiors.h"
#include "IAppModeModel.h"
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class EegeoPoiSetSearchQueryFactory : public IEegeoPoiSetSearchQueryFactory, private Eegeo::NonCopyable
                {
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                    const std::string m_serviceUrl;
                    
                public:
                    EegeoPoiSetSearchQueryFactory(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                  const std::string& serviceUrl);
                    
                    ~EegeoPoiSetSearchQueryFactory();
                    
                    IEegeoPoiSetSearchQuery* CreateEegeoOfflineSearchForQuery(Eegeo::Helpers::ICallback1<bool>& completionCallback, const std::string& devToken, const std::string& dataSetID, const bool& isVenueLabel);
                    

                };
            }
        }
    }
}
