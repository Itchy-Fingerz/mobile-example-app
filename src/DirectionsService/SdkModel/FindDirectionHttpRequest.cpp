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
                if (query.IsInterior())
                {
    // #Query the service for a route
//                    Eegeo::Space::LatLongAltitude start = Eegeo::Space::LatLongAltitude::FromDegrees(56.4602302, -2.9785768, 0);
//                    int startLevel = 0;
//                    Eegeo::Space::LatLongAltitude end = Eegeo::Space::LatLongAltitude::FromDegrees(56.4600344, -2.9783117, 0);
//                    int endLevel = 2;
//
                    Eegeo::Space::LatLongAltitude end = Eegeo::Space::LatLongAltitude::FromDegrees(56.460276, -2.978738, 0);
//                    std::string apiCall = m_requestBuilder.CreateRouteRequestWithLevels(start, startLevel,end ,endLevel);
                    
                    std::string apiCall = m_requestBuilder.CreateRouteRequestWithLevels(query.StartLocation(), query.StartLocationLevel(), end,query.EndLocationLevel());
                    m_pWebLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, apiCall, m_webRequestCompleteCallback)
                    .SetShouldCacheAggressively(false)
                    .Build();
                    
                }
                else
                {
                    std::string apiCall = m_requestBuilder.CreateRouteRequest(query.StartLocation(), query.EndLocation());
                    
                    m_pWebLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, apiCall, m_webRequestCompleteCallback)
                    .SetShouldCacheAggressively(false)
                    .Build();
                }
              
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