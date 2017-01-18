// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GeoNamesSearchServiceModule.h"

#include "EegeoJsonParser.h"
#include "GeoNamesJsonParser.h"
#include "GeoNamesSearchService.h"
#include "EegeoTagIconMapperFactory.h"
#include "GeoNamesSearchQueryFactory.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                GeoNamesSearchServiceModule::GeoNamesSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                         Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                         Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                                         const std::string& geoNamesUserName,
                                                                         const std::string& serviceUrl,
                                                                         const std::string& apiKey,
                                                                         const Search::SdkModel::SearchTags& searchTags)
                : m_pGeoNamesSearchQueryFactory(NULL)
                , m_pGeoNamesParser(NULL)
                , m_pSearchService(NULL)
                {
                    m_pGeoNamesSearchQueryFactory = Eegeo_NEW(GeoNamesSearchQueryFactory)(webRequestFactory,
                                                                                          urlEncoder,
                                                                                          serviceUrl,
                                                                                          apiKey,
                                                                                          geoNamesUserName);

                    
                    
                    m_pTagIconMapper = ExampleApp::Search::EegeoPois::SdkModel::CreateTagIconMapper(searchTags);
                    
                    m_pReadableTagMapper = Eegeo_NEW(EegeoPois::SdkModel::EegeoReadableTagMapper)(searchTags);
                    
                    m_pGeoNamesParser = Eegeo_NEW(GeoNamesJsonParser)();
                    m_pEegeoParser = Eegeo_NEW(EegeoPois::SdkModel::EegeoJsonParser)(*m_pTagIconMapper, *m_pReadableTagMapper);

                    
                    m_pSearchService = Eegeo_NEW(GeoNamesSearchService)(*m_pGeoNamesSearchQueryFactory,
                                                                        *m_pGeoNamesParser,
                                                                        networkCapabilities,
                                                                        *m_pEegeoParser);
                }
                
                GeoNamesSearchServiceModule::~GeoNamesSearchServiceModule()
                {
                    Eegeo_DELETE m_pSearchService;
                    Eegeo_DELETE m_pEegeoParser;
                    Eegeo_DELETE m_pGeoNamesParser;
                    Eegeo_DELETE m_pReadableTagMapper;
                    Eegeo_DELETE m_pGeoNamesSearchQueryFactory;

                }
                
                Search::SdkModel::ISearchService& GeoNamesSearchServiceModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }
            }
        }
    }
}
