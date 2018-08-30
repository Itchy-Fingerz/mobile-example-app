//
// Created by Najhi Ullah on 09/08/2018.
//

#include "DataSetInsertQueryFactory.h"
#include "DataSetInsertQuery.h"
#include "DataSetInsertQueryModel.h"
#include "WebPostData.h"
#include <map>


namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            const std::string m_datasetId = "d_b6a27edaf29b038cebee";

            DataSetInsertQueryFactory::DataSetInsertQueryFactory(const std::string apiUrl,
                                                                 const std::string wrldApiKey,
                                                                 Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
            : m_apiUrl(apiUrl)
            , m_wrldApiKey(wrldApiKey)
            , m_webRequestFactory(webRequestFactory)
            {

            }

            DataSetInsertQueryFactory::~DataSetInsertQueryFactory()
            {

            }

            IDataSetInsertQuery* DataSetInsertQueryFactory::CreateDataSetInsertQuery(ExampleApp::DataSet::SdkModel::DataSetInsertQueryModel& dataSetInsertQueryModel, Eegeo::Helpers::ICallback0& completionCallback)
            {
//                std::map<std::string, std::string> schema;
//                std::vector<std::string> tags;
//
//                schema["producer_guid"] = "string";
//                schema["type"] = "string";
//                schema["value"] = "double";
//                schema["userdata"] = "string";
//
//                tags[0] = "producer_guid";
//                tags[1] = "type";
//
//                ExampleApp::DataSet::SdkModel::DataSetInsertQueryModel* model = Eegeo_NEW(ExampleApp::DataSet::SdkModel::DataSetInsertQueryModel)("my-data-set", schema, tags);
                const std::string url = CreateDataSetInsertUrl();
                const std::string postData = CreateDataSetPostBody(dataSetInsertQueryModel);
                return Eegeo_NEW(DataSetInsertQuery)(url, Eegeo::Web::WebPostData::CreateTextData(postData), m_webRequestFactory, completionCallback);
            }

            const std::string DataSetInsertQueryFactory::CreateDataSetInsertUrl()
            {
                return m_apiUrl + "/datasets/" + m_datasetId + "?apikey=" + m_wrldApiKey;
            }

            const std::string DataSetInsertQueryFactory::CreateDataSetPostBody(ExampleApp::DataSet::SdkModel::DataSetInsertQueryModel& model)
            {
                std::string json = "";
                json = model.Info();
                std::string logdata = "Dataset: dispatch data " + json;
                Eegeo_TTY(logdata.c_str());
                return json;
            }
        }
    }
}