//
// Created by Najhi Ullah on 09/08/2018.
//

#include "DataSetCreationQueryModel.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            DataSetCreationQueryModel::DataSetCreationQueryModel(std::string name,
                                                                 std::map<std::string, std::string> schema,
                                                                 std::vector<std::string> tags)
            : m_name(name)
            , m_schema(schema)
            , m_tags(tags)
            {

            }

            std::string& DataSetCreationQueryModel::Name()
            {
                return m_name;
            }

            std::map<std::string, std::string>& DataSetCreationQueryModel::Schema()
            {
                return m_schema;
            }

            std::vector<std::string>& DataSetCreationQueryModel::GetTags()
            {
                return m_tags;
            }
        }
    }
}