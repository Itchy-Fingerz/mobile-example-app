//
// Created by Najhi Ullah on 09/08/2018.
//

#include "DataSetInsertQueryModel.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            DataSetInsertQueryModel::DataSetInsertQueryModel(std::string info)
            : m_info(info)
            {

            }

            std::string DataSetInsertQueryModel::Info()
            {
                return m_info;
            }
        }
    }
}