// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class IEegeoPoiSetSearchQuery
                {
                public:
                    virtual ~IEegeoPoiSetSearchQuery() { }
                    
                    virtual void Cancel() = 0;
                    
                    virtual bool IsSucceeded() = 0;
                    
                    virtual const std::string& ResponseString() = 0;
                };
            }
        }
    }
}
