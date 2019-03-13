// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "PoiDb.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class PoiDbServiceProvider: private Eegeo::NonCopyable
            {
            private:
                IPoiDbService* m_pPoiDbService;
                
                Eegeo::Helpers::TCallback1<PoiDbServiceProvider,
                IPoiDbService*> m_onResultsLoadedCallback;
                
            public:
                PoiDbServiceProvider(IPoiDbLoader& loader);

                ~PoiDbServiceProvider();
                
                bool TryGetService(IPoiDbService*& out_pDbService) const;
                
                bool IsPoiDbServiceStarted() const;
                
                void PoiDbLoaderCompleted(IPoiDbService*& pPoiDbService);
            };
        }
    }
}
