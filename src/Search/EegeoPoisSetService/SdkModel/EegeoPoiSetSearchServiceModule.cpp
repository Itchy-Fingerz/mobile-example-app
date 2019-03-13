// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoPoiSetSearchServiceModule.h"

#include "EegeoPoiSetJsonParser.h"
#include "EegeoPoiSetSearchQueryFactory.h"
#include "EegeoPoiSetReadableTagMapper.h"
#include "EegeoTagIconMapperFactory.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                EegeoPoiSetSearchServiceModule::EegeoPoiSetSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                   Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                                   const Search::SdkModel::SearchTags& searchTags,
                                                                   const std::string& serviceUrl,
                                                                   const std::vector<ApplicationConfig::SdkModel::ApplicationDataSetConfig> appConfigSet)
                : m_pEegeoSearchQueryFactory(NULL)
                , m_pEegeoParser(NULL)
                , m_pSearchService(NULL)
                , m_pTagIconMapper(NULL)
                {
                    m_pEegeoSearchQueryFactory = Eegeo_NEW(EegeoPoiSetSearchQueryFactory)(webRequestFactory,
                                                                                    serviceUrl);

                    m_pTagIconMapper = TagSearch::SdkModel::CreateTagIconMapper(searchTags);

                    m_pReadableTagMapper = Eegeo_NEW(EegeoPoiSetReadableTagMapper)(searchTags);

                    m_pEegeoParser = Eegeo_NEW(EegeoPoiSetJsonParser)(*m_pTagIconMapper, *m_pReadableTagMapper);

                    std::vector<std::string> handledTags;
                    handledTags.reserve(searchTags.tags.size());
                    for(const auto& i : searchTags.tags)
                    {
                        handledTags.push_back(i.tag);
                    }

                    m_pSearchService = Eegeo_NEW(EegeoPoiSetSearchService)(*m_pEegeoSearchQueryFactory,
                                                                     *m_pEegeoParser,
                                                                     networkCapabilities,
                                                                     handledTags,
                                                                           appConfigSet);
                    
                }
                
                EegeoPoiSetSearchServiceModule::~EegeoPoiSetSearchServiceModule()
                {
                    Eegeo_DELETE m_pSearchService;
                    Eegeo_DELETE m_pEegeoParser;
                    Eegeo_DELETE m_pTagIconMapper;
                    Eegeo_DELETE m_pReadableTagMapper;
                    Eegeo_DELETE m_pEegeoSearchQueryFactory;
                }

                IEegeoPoiSetSearchService& EegeoPoiSetSearchServiceModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }
            }
        }
    }
}
