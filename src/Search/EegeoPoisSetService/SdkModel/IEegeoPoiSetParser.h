// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "Search.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class IEegeoPoiSetParser
                {
                public:
                    virtual ~IEegeoPoiSetParser() { }
                    
                    virtual void ParseEegeoOfflineQueryResults(const std::string& serialized,
                                                            std::vector<Search::SdkModel::SearchResultModel>& out_results) = 0;
                    
                };
            }
        }
    }
}
