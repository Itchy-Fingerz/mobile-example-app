//
// Created by Najhi Ullah on 09/08/2018.
//

#pragma once

#include <string>

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class IDataSetCreationQuery
            {
            public:
                virtual ~IDataSetCreationQuery() { }

                virtual void Dispatch() = 0;

                virtual void Cancel() = 0;

                virtual bool IsSucceeded() = 0;

                virtual const std::string& ResponseString() = 0;
            };
        }
    }
}