// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoPoisLocalDBModule.h"
#include "EegeoPoisLocalDBSearchService.h"
#include "EegeoJsonParser.h"
#include "EegeoTagIconMapper.h"
#include "EegeoReadableTagMapper.h"
#include "EegeoTagIconMapperFactory.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisLocalDB
        {
            namespace SdkModel
            {
                EegeoPoisLocalDBModule::EegeoPoisLocalDBModule(Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                               const Search::SdkModel::SearchTags& searchTags,
                                                               PoiDb::SdkModel::PoiDbServiceProvider& serviceProvider)
                : m_pEegeoParser(NULL)
                , m_pSearchService(NULL)
                , m_pTagIconMapper(NULL)
                {


                    m_pTagIconMapper = TagSearch::SdkModel::CreateTagIconMapper(searchTags);

                    m_pReadableTagMapper = Eegeo_NEW(Search::EegeoPois::SdkModel::EegeoReadableTagMapper)(searchTags);

                    m_pEegeoParser = Eegeo_NEW(Search::EegeoPois::SdkModel::EegeoJsonParser)(*m_pTagIconMapper, *m_pReadableTagMapper);

                    std::vector<std::string> handledTags;
                    handledTags.reserve(searchTags.tags.size());
                    for(const auto& i : searchTags.tags)
                    {
                        handledTags.push_back(i.tag);
                    }

                    m_pSearchService = Eegeo_NEW(EegeoPoisLocalDBSearchService)(networkCapabilities,handledTags,serviceProvider);
                    
                }
                
                EegeoPoisLocalDBModule::~EegeoPoisLocalDBModule()
                {
                    Eegeo_DELETE m_pSearchService;
                    Eegeo_DELETE m_pEegeoParser;
                    Eegeo_DELETE m_pTagIconMapper;
                    Eegeo_DELETE m_pReadableTagMapper;
                }

                Search::EegeoPois::SdkModel::IEegeoParser& EegeoPoisLocalDBModule::GetEegeoParser() const
                {
                    return *m_pEegeoParser;
                }

                Search::SdkModel::ISearchService& EegeoPoisLocalDBModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }
            }
        }
    }
}
