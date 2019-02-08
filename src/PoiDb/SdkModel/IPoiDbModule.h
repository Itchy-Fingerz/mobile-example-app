// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "PoiDb.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class IPoiDbModule
            {
            public:
                virtual ~IPoiDbModule() { }
                virtual bool IsPoiDbServiceStarted() const = 0;
                virtual bool TryGetPoiDbService(IPoiDbService*& out_pService) const = 0;
                virtual PoiDbServiceProvider& GetPoiDbServiceProvider() const = 0;
            };
        }
    }
}
