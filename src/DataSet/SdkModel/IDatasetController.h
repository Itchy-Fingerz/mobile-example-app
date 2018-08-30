//
// Created by Najhi Ullah on 09/08/2018.
//

#pragma once

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class IDataSetController
            {
            public:
                virtual ~IDataSetController() {};

                virtual void Update(float dt) = 0;
            };
        }
    }
}
