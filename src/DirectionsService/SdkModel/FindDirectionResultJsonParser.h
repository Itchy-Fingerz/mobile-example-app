// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "Types.h"
#include <sstream>
#include "document.h"
#include "DirectionResultModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionResultJsonParser : private Eegeo::NonCopyable
            {
                
            public:
                
                FindDirectionResultJsonParser();
                ~FindDirectionResultJsonParser();
                DirectionResultModel ParseGeoNamesQueryResults(const std::string& serialized);
                
            private:
                
                std::vector<std::string> TokenizeString(std::string mainString , std::string delimiter, bool skipFirstchar);
                int GetBuildingLevel(const rapidjson::Value& stepNextValue);


            };
        }
    }
}
