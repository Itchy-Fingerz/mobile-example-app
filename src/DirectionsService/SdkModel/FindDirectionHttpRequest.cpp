// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IWebLoadRequest.h"
#include "FindDirectionHttpRequest.h"
#include "RoutingRequestBuilder.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            FindDirectionHttpRequest::FindDirectionHttpRequest(const std::string& requestUrl,
                                                               Eegeo::Helpers::ICallback0& completionCallback,
                                                               Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                               const Eegeo::Routes::Webservice::RoutingRequestBuilder& requestBuilder,
                                                               Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                               const FindDirectionQuery& query,
                                                               const std::string& eegeoApiKey)
            : m_pWebLoadRequest(NULL)
            , m_completionCallback(completionCallback)
            , m_responseString()
            , m_dispatched(false)
            , m_isSuccess(false)
            , m_webRequestFactory(webRequestFactory)
            , m_requestBuilder(requestBuilder)
            , m_webRequestCompleteCallback(this, &FindDirectionHttpRequest::HandleWebResponseComplete)
            {
//              
//                std::string startLocLat = std::to_string(query.StartLocation().GetLatitudeInDegrees());
//                std::string startLocLong = std::to_string(query.StartLocation().GetLongitudeInDegrees());
//                
//                std::string endLocLat = std::to_string(query.EndLocation().GetLatitudeInDegrees());
//                std::string endLocLong = std::to_string(query.EndLocation().GetLongitudeInDegrees());
//                //loc=37.7858,-122.401%3B37.7869000,-122.402333&apikey=b488cb833b4d73f0ff4662160743e8f2
//                std::string url =requestUrl
//                + "loc=" + startLocLong + "," + startLocLat + "%3B" + endLocLong+ "," + endLocLat + "&apikey="
//                + eegeoApiKey;
//                m_pWebLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_webRequestCompleteCallback).Build();
                
                // Query the service for a route
                Eegeo::Space::LatLongAltitude start = Eegeo::Space::LatLongAltitude::FromDegrees(56.4602302, -2.9785768, 0);
                int startLevel = 0;
                Eegeo::Space::LatLongAltitude end = Eegeo::Space::LatLongAltitude::FromDegrees(56.4600344, -2.9783117, 0);
                int endLevel = 2;
                
                std::string apiCall = m_requestBuilder.CreateRouteRequestWithLevels(start, startLevel, end, endLevel);
                m_pWebLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, apiCall, m_webRequestCompleteCallback)
                .SetShouldCacheAggressively(false)
                .Build();
//                webRequest->Load();
                
            }
            
            FindDirectionHttpRequest::~FindDirectionHttpRequest()
            {
            
            }
            
            void FindDirectionHttpRequest::Dispatch()
            {
                Eegeo_ASSERT(!m_dispatched, "Cannot dispatch Find Direction Request if query has already been dispatched.\n");
                
                m_dispatched = true;
                m_pWebLoadRequest->Load();
            }
            
            void FindDirectionHttpRequest::Cancel()
            {
                Eegeo_ASSERT(m_dispatched, "Cannot cancel Find Direction Request until query has been dispatched.\n");
                
                m_pWebLoadRequest->Cancel();
                Eegeo_DELETE this;
            }
            
            void FindDirectionHttpRequest::HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse)
            {
                Eegeo_ASSERT(!webResponse.IsCancelled());
                
                size_t resultSize = webResponse.GetBodyData().size();
                
                m_isSuccess = webResponse.IsSucceeded();
                
                m_responseString = (resultSize > 0) ? std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize) : "<empty>";
                
                m_completionCallback();
                
                Eegeo_DELETE this;
            }
            
            bool FindDirectionHttpRequest::IsSucceeded()
            {
                return m_isSuccess;
            }
            
            const std::string& FindDirectionHttpRequest::ResponseString()
            {
                return m_responseString;
            }
        }
    }
}