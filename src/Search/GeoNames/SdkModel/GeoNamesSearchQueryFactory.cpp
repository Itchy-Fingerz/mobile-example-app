// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GeoNamesSearchQueryFactory.h"
#include "GeoNamesSearchQuery.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorId.h"
#include "EegeoSearchQuery.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                GeoNamesSearchQueryFactory::GeoNamesSearchQueryFactory(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                       Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                       const std::string& serviceUrl,
                                                                       const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                                                       const std::string& geoNamesUserName)
                : m_webRequestFactory(webRequestFactory)
                , m_urlEncoder(urlEncoder)
                , m_geoNamesUserName(geoNamesUserName)
                , m_serviceUrl(serviceUrl)
                , m_apiTokenModel(apiTokenModel)
                {
                    
                }
                
                GeoNamesSearchQueryFactory::~GeoNamesSearchQueryFactory()
                {
                    
                }
                
                EegeoPois::SdkModel::IEegeoSearchQuery* GeoNamesSearchQueryFactory::CreateGeoNamesSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                                               Eegeo::Helpers::ICallback0& completionCallback)
                {
                    if (query.ShouldTryInteriorSearch())
                    {
                        
                        const std::string InteriorId = "westport_house";
                        
                        const std::string& id = "";
                        
                        const Eegeo::Resources::Interiors::InteriorId& interiorId(id);
                        
                        return Eegeo_NEW(EegeoPois::SdkModel::EegeoSearchQuery)(m_webRequestFactory,
                                                           m_urlEncoder,
                                                           query,
                                                           m_serviceUrl,
                                                           m_apiTokenModel,
                                                            interiorId,
                                                           2,
                                                           completionCallback);
                    }
                    else
                    {
                        return Eegeo_NEW(GeoNamesSearchQuery)(m_webRequestFactory,
                                                              m_urlEncoder,
                                                              query,
                                                              completionCallback,
                                                              m_geoNamesUserName);
                    }

                }
            }
        }
    }
}
