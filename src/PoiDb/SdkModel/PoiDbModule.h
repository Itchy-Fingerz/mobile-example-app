// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "PoiDb.h"

#include "IPoiDbModule.h"
#include "Types.h"
#include "IFileIO.h"
#include "IEegeoPoiSetSearchService.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class PoiDbModule: public IPoiDbModule, private Eegeo::NonCopyable
            {
            private:
                ExampleApp::PoiDb::SdkModel::PoiDbServiceProvider* m_pPoiDbServiceProvider;
                ExampleApp::PoiDb::SdkModel::IPoiDbLoader *m_pPoiDBLoader;

            public:
                PoiDbModule(Eegeo::Helpers::IFileIO& fileIO, ExampleApp::Search::EegeoPoisSetService::SdkModel::IEegeoPoiSetSearchService &searchService);

                ~PoiDbModule();
   
                virtual bool IsPoiDbServiceStarted() const;
                
                virtual bool TryGetPoiDbService(IPoiDbService*& out_pService) const;
                
                virtual PoiDbServiceProvider& GetPoiDbServiceProvider() const;
            };
        }
    }
}
