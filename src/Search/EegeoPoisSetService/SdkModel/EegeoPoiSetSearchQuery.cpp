// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoPoiSetSearchQuery.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "ApiTokenModel.h"
#include "InteriorId.h"

#include <sstream>
#include <iomanip>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                EegeoPoiSetSearchQuery::EegeoPoiSetSearchQuery(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                   const std::string& serviceUrl,
                                                   Eegeo::Helpers::ICallback0& completionCallback)
                : m_completionCallback(completionCallback)
                , m_responseString("")
                , m_isSuccess(false)
                , m_webRequestCompleteCallback(this, &EegeoPoiSetSearchQuery::OnWebResponseReceived)
                {
                    std::stringstream urlstream;
                    urlstream.setf(std::ios_base::fixed);
                    // TODO: This URL needs to be moved to standard_config.json
                    urlstream << "https://poi.wrld3d.com/v1.1";
                    urlstream << "/poisets/6355/pois/?token=5294e58996cefc079bb410e3ab2582eeb96d95e414383f439aee799404dcd97201ffaed84109dfc7";

                    std::string url = urlstream.str();
                    m_pWebLoadRequest = webRequestFactory
                        .Begin(Eegeo::Web::HttpVerbs::GET, url, m_webRequestCompleteCallback)
                        .SetShouldCacheAggressively(false)
                        .SetShouldRequestOnlyFromCache(false)
                        .Build();
                    m_pWebLoadRequest->Load();
                }
                
                EegeoPoiSetSearchQuery::~EegeoPoiSetSearchQuery()
                {                    
                }
                
                void EegeoPoiSetSearchQuery::Cancel()
                {
                    m_pWebLoadRequest->Cancel();
                }
                
                bool EegeoPoiSetSearchQuery::IsSucceeded()
                {
                    return m_isSuccess;
                }
                
                const std::string& EegeoPoiSetSearchQuery::ResponseString()
                {
                    return m_responseString;
                }
                
                void EegeoPoiSetSearchQuery::OnWebResponseReceived(Eegeo::Web::IWebResponse& webResponse)
                {
                    if(webResponse.IsSucceeded())
                    {
                        size_t resultSize = webResponse.GetBodyData().size();
                        m_responseString = std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize);
                        m_isSuccess = true;
                    }
                    
                    m_completionCallback();
                }
            }
        }
    }
}
