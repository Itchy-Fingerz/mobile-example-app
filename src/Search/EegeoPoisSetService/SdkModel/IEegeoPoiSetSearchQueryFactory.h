// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include <string>
#include "Search.h"
#include "ICallback.h"
#include "EegeoPoisSetService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class IEegeoPoiSetSearchQueryFactory
                {
                public:
                    virtual ~IEegeoPoiSetSearchQueryFactory() { }
                    
                    virtual IEegeoPoiSetSearchQuery* CreateEegeoOfflineSearchForQuery(Eegeo::Helpers::ICallback0& completionCallback, const std::string& devToken, const std::string& dataSetID) = 0;
                };
            }
        }
    }
}
