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
            class IDataSetCreationQueryFactory
            {
            public:
                virtual ~IDataSetCreationQueryFactory() { }

                virtual IDataSetCreationQuery* CreateDataSetCreationQuery(Eegeo::Helpers::ICallback0& completionCallback) = 0;

            };
        }
    }
}