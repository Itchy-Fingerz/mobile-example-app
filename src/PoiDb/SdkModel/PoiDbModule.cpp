// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiDbModule.h"
#include "PoiDbServiceProvider.h"
#include "PoiDbLoader.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            PoiDbModule::PoiDbModule(Eegeo::Helpers::IFileIO& fileIO, ExampleApp::Search::EegeoPoisSetService::SdkModel::IEegeoPoiSetSearchService &searchService,
                                                     const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                     Eegeo::Concurrency::Tasks::IWorkPool& workPool)
            {
                m_pPoiDBLoader = Eegeo_NEW(ExampleApp::PoiDb::SdkModel::PoiDbLoader)(fileIO.GetAppFilePathname("pois.db"), searchService, interiorInteractionModel, workPool);
                m_pPoiDbServiceProvider = Eegeo_NEW(ExampleApp::PoiDb::SdkModel::PoiDbServiceProvider)(*m_pPoiDBLoader);
                m_pPoiDBLoader->CreateDbConnection();
            }

            PoiDbModule::~PoiDbModule()
            {
                Eegeo_DELETE(m_pPoiDbServiceProvider);
                Eegeo_DELETE(m_pPoiDBLoader);
            }
            
            bool PoiDbModule::IsPoiDbServiceStarted() const
            {
                return m_pPoiDbServiceProvider->IsPoiDbServiceStarted();
            }

            bool PoiDbModule::TryGetPoiDbService(IPoiDbService*& out_pService) const
            {
                return m_pPoiDbServiceProvider->TryGetService(out_pService);
            }
            
            PoiDbServiceProvider& PoiDbModule::GetPoiDbServiceProvider() const
            {
                return *m_pPoiDbServiceProvider;
            }
        }
    }
}
