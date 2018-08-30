//
// Created by Najhi Ullah on 09/08/2018.
//

#pragma once

#include <string>
#include "DataSet.h"
#include "ICallback.h"
#include "IDataSetCreationQueryFactory.h"
#include "Web.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class DataSetCreationQueryFactory : public IDataSetCreationQueryFactory
            {
            public:
                DataSetCreationQueryFactory(const std::string apiUrl,
                                            const std::string wrldApiKey,
                                            Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
                ~DataSetCreationQueryFactory();
                IDataSetCreationQuery* CreateDataSetCreationQuery(Eegeo::Helpers::ICallback0& completionCallback);
//                DataSetCreationQueryModel* m_pDataSetCreationQueryModel;

            private:
                const std::string CreateDataSetCreationUrl();
                const std::string CreateDataSetPostBody();
                const std::string m_apiUrl;
                const std::string m_wrldApiKey;
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;

            };
        }
    }
}
