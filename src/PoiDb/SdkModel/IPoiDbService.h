// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include <string>
#include <vector>
#include "Search.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class IPoiDbService
            {
            public:
                virtual ~IPoiDbService() { }
                virtual void FetchPoisWithQuery(const Search::SdkModel::SearchQuery& query,std::vector<Search::SdkModel::SearchResultModel>& outPutResults) = 0;
                virtual void FetchVenuesLabelsWithQuery(std::vector<Search::SdkModel::SearchResultModel>& outPutResults) = 0;
            };
        }
    }
}
