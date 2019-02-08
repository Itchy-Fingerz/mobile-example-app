// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"
#include "NetIncludes.h"
#include "ITagIconMapper.h"
#include "SearchTags.h"
#include "EegeoPois.h"
#include "PoiDb.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisLocalDB
        {
            namespace SdkModel
            {
                class EegeoPoisLocalDBModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
                {
                private:
                    Search::EegeoPois::SdkModel::IEegeoParser* m_pEegeoParser;
                    Search::SdkModel::ISearchService* m_pSearchService;

                    TagSearch::SdkModel::ITagIconMapper* m_pTagIconMapper;
                    Search::EegeoPois::SdkModel::EegeoReadableTagMapper* m_pReadableTagMapper;
                public:
                    EegeoPoisLocalDBModule(Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                           const Search::SdkModel::SearchTags& searchTags,
                                           PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider);
                    
                    ~EegeoPoisLocalDBModule();

                    Search::EegeoPois::SdkModel::IEegeoParser& GetEegeoParser() const;
                    Search::SdkModel::ISearchService& GetSearchService() const;
                };
            }
        }
    }
}
