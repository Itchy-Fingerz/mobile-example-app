// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "Types.h"
#include "SearchTags.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class EegeoPoiSetReadableTagMapper : private Eegeo::NonCopyable
                {
                public:
                    EegeoPoiSetReadableTagMapper(const Search::SdkModel::SearchTags& searchTags);
                    
                    const std::string& GetNameForTag(const std::string& tag) const;
                    
                private:
                    std::map<std::string, const std::string> m_tagsToReadableNamesMap;
                    std::string m_unknownTagName;
                };
            }
        }
    }
}
