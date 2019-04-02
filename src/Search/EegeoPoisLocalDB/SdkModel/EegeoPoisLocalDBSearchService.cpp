// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoPoisLocalDBSearchService.h"
#include "INetworkCapabilities.h"
#include "SearchResultModel.h"
#include "PoiDbService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisLocalDB
        {
            namespace SdkModel
            {
                EegeoPoisLocalDBSearchService::EegeoPoisLocalDBSearchService(Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                               const std::vector<std::string>& handledTags,PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider)
                : Search::SdkModel::SearchServiceBase(handledTags, true)
                , m_networkCapabilities(networkCapabilities)
                , m_dbServiceProvider(serviceProvider)
                , m_currentQueryModel()
                , m_hasActiveQuery(false)
                , m_networkCapabilitiesChangedHandler(this, &EegeoPoisLocalDBSearchService::HandleNetworkCapabilitiesChanged)
                {
                    m_networkCapabilities.RegisterChangedCallback(m_networkCapabilitiesChangedHandler);
                }
                
                EegeoPoisLocalDBSearchService::~EegeoPoisLocalDBSearchService()
                {
                    CancelInFlightQueries();
                    m_networkCapabilities.UnregisterChangedCallback(m_networkCapabilitiesChangedHandler);
                }
                
                void EegeoPoisLocalDBSearchService::CancelInFlightQueries()
                {
                    //TODO: Cancel Local Database Queries
                    m_hasActiveQuery = false;

                }
                
                void EegeoPoisLocalDBSearchService::PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query)
                {
                    if(!m_networkCapabilities.NetworkAvailable())
                    {
                        std::vector<Search::SdkModel::SearchResultModel> outPutResults;
                        if(m_dbServiceProvider.IsPoiDbServiceStarted()) {
                            ExampleApp::PoiDb::SdkModel::IPoiDbService* service = NULL;
                            m_dbServiceProvider.TryGetService(service);
                            if(service != NULL)
                            {
                                service->FetchPoisWithQuery(query,outPutResults);
                                ExecutQueryResponseReceivedCallbacks(true, query, outPutResults);

                            }
                        }
                    }
                    else
                    {
                        std::vector<Search::SdkModel::SearchResultModel> outPutResults;
                        ExecutQueryResponseReceivedCallbacks(false, query, outPutResults);

                    }
                }

                void EegeoPoisLocalDBSearchService::PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                  Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    Search::SdkModel::IdentitySearchCallbackData result = Search::SdkModel::IdentitySearchCallbackData::CreateFailed(outdatedSearchResult);
                    callback(result);
                }
                
                void EegeoPoisLocalDBSearchService::HandleNetworkCapabilitiesChanged()
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
