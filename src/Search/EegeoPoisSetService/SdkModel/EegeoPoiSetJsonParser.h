// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "IEegeoPoiSetParser.h"
#include "Types.h"
#include "SearchResultModel.h"
#include "EegeoPois.h"
#include "TagSearch.h"
#include "EegeoPoiSetReadableTagMapper.h"
namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class EegeoPoiSetJsonParser : public IEegeoPoiSetParser, private Eegeo::NonCopyable
                {
                private:
                    const TagSearch::SdkModel::ITagIconMapper& m_tagIconMapper;
                    const EegeoPoiSetReadableTagMapper& m_tagReadableNameMapper;

                public:
                    EegeoPoiSetJsonParser(const TagSearch::SdkModel::ITagIconMapper& tagIconMapper,
                                    const EegeoPoiSetReadableTagMapper& tagReadableNameMapper);
                    
                    void ParseEegeoOfflineQueryResults(const std::string& serialized,
                                                std::vector<Search::SdkModel::SearchResultModel>& out_results);
                };

                //EegeoPoiSetSearchResultModel TransformToEegeoSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                
                //bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl);
            }
        }
    }
}
