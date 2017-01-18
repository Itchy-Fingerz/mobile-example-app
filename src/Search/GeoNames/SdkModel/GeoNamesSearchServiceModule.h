// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"
#include "UrlHelpers.h"
#include "Web.h"
#include "GeoNames.h"
#include "NetIncludes.h"
#include "Search.h"
#include "IEegeoParser.h"
#include "SearchTags.h"
#include "ITagIconMapper.h"
#include "InteriorInteractionModel.h"
#include "EegeoReadableTagMapper.h"



namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class GeoNamesSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
                {
                private:
                    IGeoNamesSearchQueryFactory* m_pGeoNamesSearchQueryFactory;
                    IGeoNamesParser* m_pGeoNamesParser;
                    EegeoPois::SdkModel::IEegeoParser* m_pEegeoParser;

                    Search::SdkModel::ISearchService* m_pSearchService;
                    SearchResultPoi::SdkModel::ITagIconMapper *m_pTagIconMapper;
                    EegeoPois::SdkModel::EegeoReadableTagMapper *m_pReadableTagMapper;

                public:
                    GeoNamesSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                const std::string& geoNamesUserName,
                                                const std::string& serviceUrl,
                                                const std::string& apiKey,
                                                const Search::SdkModel::SearchTags& searchTags);
                    
                    ~GeoNamesSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                };
            }
        }
    }
}