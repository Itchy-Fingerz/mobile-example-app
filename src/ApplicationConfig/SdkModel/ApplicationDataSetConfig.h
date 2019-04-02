// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            struct ApplicationDataSetConfig
            {
                std::string devToken;
                std::string dataSetId;
                bool isVenueLabel;
                ApplicationDataSetConfig(
                    const std::string& devToken,
                    const std::string& dataSetId,
                    const bool isVenueLabel)
                : devToken(devToken)
                , dataSetId(dataSetId)
                , isVenueLabel(isVenueLabel)
                {

                }
            };
        }
    }
}
