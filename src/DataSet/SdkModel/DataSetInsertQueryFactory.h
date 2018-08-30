//
// Created by Najhi Ullah on 09/08/2018.
//

#pragma once

#include <string>
#include "DataSet.h"
#include "ICallback.h"
#include "IDataSetInsertQueryFactory.h"
#include "Web.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class DataSetInsertQueryFactory : public IDataSetInsertQueryFactory
            {
            public:
                DataSetInsertQueryFactory(const std::string apiUrl,
                                            const std::string wrldApiKey,
                                            Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
                ~DataSetInsertQueryFactory();
                IDataSetInsertQuery* CreateDataSetInsertQuery(ExampleApp::DataSet::SdkModel::DataSetInsertQueryModel& dataSetInsertQueryModel, Eegeo::Helpers::ICallback0& completionCallback);

            private:
                const std::string CreateDataSetInsertUrl();
                const std::string CreateDataSetPostBody(ExampleApp::DataSet::SdkModel::DataSetInsertQueryModel& model);
                const std::string m_apiUrl;
                const std::string m_wrldApiKey;
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;

            };
        }
    }
}
