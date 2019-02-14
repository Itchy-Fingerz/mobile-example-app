// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoPoiSetSearchService.h"

#include "EegeoPoiSetSearchQuery.h"
#include "EegeoPoiSetSearchQueryFactory.h"
#include "IEegeoPoiSetParser.h"
#include "INetworkCapabilities.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                EegeoPoiSetSearchService::EegeoPoiSetSearchService(IEegeoPoiSetSearchQueryFactory& EegeoSearchQueryFactory,
                                                               IEegeoPoiSetParser& EegeoParser,
                                                               Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                               const std::vector<std::string>& handledTags)
                : m_eeGeoSearchQueryFactory(EegeoSearchQueryFactory)
                , m_eeGeoParser(EegeoParser)
                , m_networkCapabilities(networkCapabilities)
                , m_searchCallback(this,&EegeoPoiSetSearchService::HandleSearchResponse)
                , m_pCurrentRequest(NULL)
                , m_hasActiveQuery(false)
                , m_networkCapabilitiesChangedHandler(this, &EegeoPoiSetSearchService::HandleNetworkCapabilitiesChanged)
                {
                    m_networkCapabilities.RegisterChangedCallback(m_networkCapabilitiesChangedHandler);
                }
                
                EegeoPoiSetSearchService::~EegeoPoiSetSearchService()
                {
                    CancelInFlightQueries();
                    m_networkCapabilities.UnregisterChangedCallback(m_networkCapabilitiesChangedHandler);
                }
                
                
                void EegeoPoiSetSearchService::CancelInFlightQueries()
                {
                    if(m_pCurrentRequest != NULL)
                    {
                        if(m_hasActiveQuery)
                        {
                            m_pCurrentRequest->Cancel();
                        }
                        Eegeo_DELETE m_pCurrentRequest;
                        m_pCurrentRequest = NULL;
                    }
                    m_hasActiveQuery = false;
                }
                
                void EegeoPoiSetSearchService::PerformLocationSearchForDBInsertion()
                {
                    CancelInFlightQueries();
                    if(!m_networkCapabilities.NetworkAvailable())
                    {
                        return;
                    }
                    m_hasActiveQuery = true;
                    m_pCurrentRequest = m_eeGeoSearchQueryFactory.CreateEegeoOfflineSearchForQuery(m_searchCallback);
                    
                }
                                
                void EegeoPoiSetSearchService::InsertOnReceivedQueryResultsForLocalDBCallback(Eegeo::Helpers::ICallback2<const bool&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback)
                {
                    m_queryResponseReceivedCallbacks.AddCallback(callback);

                }
                
                void EegeoPoiSetSearchService::RemoveOnReceivedQueryResultsForLocalDBCallback(Eegeo::Helpers::ICallback2<const bool&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback)
                {
                    m_queryResponseReceivedCallbacks.RemoveCallback(callback);
                }
                
                void EegeoPoiSetSearchService::HandleSearchResponse()
                {
                    std::vector<Search::SdkModel::SearchResultModel> queryResults;
                    if(m_pCurrentRequest != NULL && m_pCurrentRequest->IsSucceeded())  // Needs NULL check because callback can happen before factory returns query
                    {
                        const std::string& response(m_pCurrentRequest->ResponseString());
                        m_eeGeoParser.ParseEegeoOfflineQueryResults(response, queryResults);
                    }
                    
                    m_hasActiveQuery = false;
                    if (m_pCurrentRequest != NULL)
                    {
                        // Insert In DB
                        m_queryResponseReceivedCallbacks.ExecuteCallbacks(m_pCurrentRequest->IsSucceeded(), queryResults);

                    }
                }
                
                void EegeoPoiSetSearchService::HandleNetworkCapabilitiesChanged()
                {
                    if (!m_networkCapabilities.NetworkAvailable())
                    {
                        CancelInFlightQueries();
                    }
                }
                

            }
        }
    }
}
