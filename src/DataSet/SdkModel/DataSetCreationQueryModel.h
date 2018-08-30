//
// Created by Najhi Ullah on 09/08/2018.
//

#pragma once

#include <string>
#include <map>
#include <vector>

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class DataSetCreationQueryModel
            {
            public:
                DataSetCreationQueryModel(std::string name,
                                          std::map<std::string, std::string> schema,
                                          std::vector<std::string> tags);

                std::string& Name();
                std::map<std::string, std::string>& Schema();
                std::vector<std::string>& GetTags();

            private:
                std::string m_name;
                std::map<std::string, std::string> m_schema;
                std::vector<std::string> m_tags;
            };
        }
    }
}
