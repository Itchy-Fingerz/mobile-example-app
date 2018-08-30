//
// Created by Najhi Ullah on 09/08/2018.
//

#pragma once

#include <string>
#include "DataSet.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class IDataSetInsertQueryFactory
            {
            public:
                virtual ~IDataSetInsertQueryFactory() { }

                virtual IDataSetInsertQuery* CreateDataSetInsertQuery(ExampleApp::DataSet::SdkModel::DataSetInsertQueryModel& dataSetInsertQueryModel, Eegeo::Helpers::ICallback0& completionCallback) = 0;

            };
        }
    }
}