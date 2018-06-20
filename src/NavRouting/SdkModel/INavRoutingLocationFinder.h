#pragma once

#include "NavRouting.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class INavRoutingLocationFinder
            {
            public:
                virtual ~INavRoutingLocationFinder() {};

                virtual bool TryGetCurrentLocation(NavRoutingLocationModel &outLocation) = 0;

                virtual bool TryGetLocationFromNavigationMessage(
                        const NavRouting::NavigateToMessage& navigateToMessage,
                        NavRoutingLocationModel &outLocation) = 0;
            };
        }
    }
}
