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
                if (query.StartBuildingID() != "" && query.EndBuildingID() != "" &&  query.StartBuildingID() != query.EndBuildingID())   // multipart request b/w buildings
                {
                    //#Multipart
                    
                    Eegeo::Space::LatLongAltitude start = query.StartLocation();
                    Eegeo::Space::LatLongAltitude end = query.EndLocation();
                    
                    
                    std::string startLocLat = std::to_string(start.GetLatitudeInDegrees());
                    std::string startLocLong = std::to_string(start.GetLongitudeInDegrees());
                    
                    
                    std::string endLocLat = std::to_string(end.GetLatitudeInDegrees());
                    std::string endLocLong = std::to_string(end.GetLongitudeInDegrees());
                    std::string url = requestUrl+ "multiroute/?" + "loc=" + startLocLong + "," + startLocLat + "%3B" + endLocLong+ "," + endLocLat + "&levels="+std::to_string(query.StartLocationLevel()) + "%3B"+std::to_string(query.EndLocationLevel())+"&apikey="
                    + eegeoApiKey+"&limit=400";
                    
                    
                    m_pWebLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_webRequestCompleteCallback).Build();

                    
                }
                else if  (query.StartBuildingID() != "" && query.EndBuildingID() != "") // Indoor ROute Case
                {
                    std::string apiCall = m_requestBuilder.CreateRouteRequestWithLevels(query.StartLocation(), query.StartLocationLevel(), query.EndLocation(),query.EndLocationLevel());
                    m_pWebLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, apiCall, m_webRequestCompleteCallback)
                    .SetShouldCacheAggressively(false)
                    .Build();
                }else if (query.StartBuildingID() != "" && query.EndBuildingID() == "")  // Indoor to Outdoor
                {
                    Eegeo::Space::LatLongAltitude start = query.StartLocation();
                    Eegeo::Space::LatLongAltitude end = query.EndLocation();
                    
                    
                    std::string startLocLat = std::to_string(start.GetLatitudeInDegrees());
                    std::string startLocLong = std::to_string(start.GetLongitudeInDegrees());
                    
                    
                    std::string endLocLat = std::to_string(end.GetLatitudeInDegrees());
                    std::string endLocLong = std::to_string(end.GetLongitudeInDegrees());
                    std::string url = requestUrl+ "route?" + "loc=" + startLocLong + "," + startLocLat + ","+std::to_string(query.StartLocationLevel())+"%3B" + endLocLong+ "," + endLocLat + "&apikey="
                    + eegeoApiKey;
                    
                    
                    m_pWebLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_webRequestCompleteCallback).Build();
                }
                else if (query.EndBuildingID() != "" && query.StartBuildingID() == "")  // Outdoor to indoor
                {
                    Eegeo::Space::LatLongAltitude start = query.StartLocation();
                    Eegeo::Space::LatLongAltitude end = query.EndLocation();
                    
                    
                    std::string startLocLat = std::to_string(start.GetLatitudeInDegrees());
                    std::string startLocLong = std::to_string(start.GetLongitudeInDegrees());
                    
                    
                    std::string endLocLat = std::to_string(end.GetLatitudeInDegrees());
                    std::string endLocLong = std::to_string(end.GetLongitudeInDegrees());
                    std::string url = requestUrl+ "route?" + "loc=" + startLocLong + "," + startLocLat + "%3B" + endLocLong+ "," + endLocLat + ","+std::to_string(query.EndLocationLevel())+ "&apikey="
                    + eegeoApiKey;
                    
                    
                    m_pWebLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_webRequestCompleteCallback).Build();
                }
                else  // Outdoor route
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