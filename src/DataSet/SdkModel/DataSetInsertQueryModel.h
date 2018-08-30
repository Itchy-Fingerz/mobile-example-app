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
            class DataSetInsertQueryModel
            {
            public:
                DataSetInsertQueryModel(std::string info);

                std::string Info();

            private:
                std::string m_info;
            };
        }
    }
}
