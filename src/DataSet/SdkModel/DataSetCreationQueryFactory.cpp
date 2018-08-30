//
// Created by Najhi Ullah on 09/08/2018.
//

#include "DataSetCreationQueryFactory.h"
#include "DataSetCreationQuery.h"
#include "DataSetCreationQueryModel.h"
#include "WebPostData.h"
#include <map>


namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            DataSetCreationQueryFactory::DataSetCreationQueryFactory(const std::string apiUrl,
                                                                     const std::string wrldApiKey,
                                                                     Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
            : m_apiUrl(apiUrl)
            , m_wrldApiKey(wrldApiKey)
            , m_webRequestFactory(webRequestFactory)
//            , m_pDataSetCreationQueryModel(NULL)
            {

            }

            DataSetCreationQueryFactory::~DataSetCreationQueryFactory()
            {

            }

            IDataSetCreationQuery* DataSetCreationQueryFactory::CreateDataSetCreationQuery(Eegeo::Helpers::ICallback0& completionCallback)
            {
//                std::map<std::string, std::string> schema;
//
//                schema["producer_guid"] = "string";
//                schema["type"] = "string";
//                schema["value"] = "double";
//                schema["userdata"] = "string";
//
//                std::vector<std::string> tags(2);
//                tags[0] = "producer_guid";
//                tags[1] = "type";

//                m_pDataSetCreationQueryModel = Eegeo_NEW(ExampleApp::DataSet::SdkModel::DataSetCreationQueryModel)("my-data-set", schema, tags);
                const std::string url = CreateDataSetCreationUrl();
                const std::string postData = CreateDataSetPostBody();

                return Eegeo_NEW(DataSetCreationQuery)(url, Eegeo::Web::WebPostData::CreateTextData(postData), m_webRequestFactory, completionCallback);
            }

            const std::string DataSetCreationQueryFactory::CreateDataSetCreationUrl()
            {
                return m_apiUrl + "/datasets?apikey=" + m_wrldApiKey;
            }

            const std::string DataSetCreationQueryFactory::CreateDataSetPostBody()
            {
                std::string json = "";

//                std::string tempSchema = "";
//                std::string tempTags = "";
//
//                std::map<std::string, std::string> map = m_pDataSetCreationQueryModel->Schema();
//                for(std::map<std::string, std::string>::iterator it=map.begin(); it!=map.end() ; ++it)
//                {
//                    tempSchema += "{\"name\":\""+it->first+"\",\"type\":\""+it->second+"\"},";
//                }
//                std::string schema = tempSchema.substr(0, tempSchema.size() - 1);
//
//                std::vector<std::string> vector = m_pDataSetCreationQueryModel->GetTags();
//                for(std::vector<std::string>::iterator it = vector.begin() ; it != vector.end() ; ++it)
//                {
//                    tempTags += "\"" + *it + "\",";
//                }
//                std::string tags = tempTags.substr(0, tempTags.size() - 1);

//                json = "{\"name\":\"" + m_pDataSetCreationQueryModel->Name() + "\"," +
//                        "\"schema\":[" + schema + "]," +
//                        "\"tags\":[" + tags + "]}";

                std::string schema = "{\"name\":\"producer_guid\",\"type\":\"string\"},"
                                     "{\"name\":\"type\",\"type\":\"string\"},"
                                     "{\"name\":\"value\",\"type\":\"double\"},"
                                     "{\"name\":\"userdata\",\"type\":\"string\"}";

                std::string tags = "\"producer_guid\","
                                   "\"type\"";

                json = "{\"name\":\"my-data-set\",\"schema\":[" + schema + "],\"tags\":[" + tags + "]}";

                return json;
            }
        }
    }
}