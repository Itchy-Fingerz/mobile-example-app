// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoPoiSetSearchQueryFactory.h"
#include "EegeoPoiSetSearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                EegeoPoiSetSearchQueryFactory::EegeoPoiSetSearchQueryFactory(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                 const std::string& serviceUrl)
                : m_webRequestFactory(webRequestFactory)
                , m_serviceUrl(serviceUrl)
                {
                }
                
                EegeoPoiSetSearchQueryFactory::~EegeoPoiSetSearchQueryFactory()
                {
                }
                
                IEegeoPoiSetSearchQuery* EegeoPoiSetSearchQueryFactory::CreateEegeoOfflineSearchForQuery(Eegeo::Helpers::ICallback1<bool>& completionCallback, const std::string& devToken, const std::string& dataSetID, const bool& isVenueLabel)
                {
                    return Eegeo_NEW(EegeoPoiSetSearchQuery)(m_webRequestFactory,
                                                             m_serviceUrl,
                                                             devToken,
                                                             dataSetID,
                                                             isVenueLabel,
                                                             completionCallback);
                }
            }
        }
    }
}
