// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiDbServiceProvider.h"
#include "PoiDbService.h"
#include "PoiDbLoader.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            PoiDbServiceProvider::PoiDbServiceProvider(IPoiDbLoader& loader)
            : m_pPoiDbService(NULL),
            m_onResultsLoadedCallback(this, &PoiDbServiceProvider::PoiDbLoaderCompleted)
            {
                loader.InsertOnDbServiceStartedCallback(m_onResultsLoadedCallback);
            }

            PoiDbServiceProvider::~PoiDbServiceProvider()
            {
                Eegeo_DELETE m_pPoiDbService;
            }
            
            bool PoiDbServiceProvider::TryGetService(IPoiDbService*& out_pDbService) const
            {
                out_pDbService = m_pPoiDbService;
                return (m_pPoiDbService != NULL);
            }
            
            bool PoiDbServiceProvider::IsPoiDbServiceStarted() const
            {
                return m_pPoiDbService != NULL;
            }
            
            void PoiDbServiceProvider::PoiDbLoaderCompleted(IPoiDbService*& pPoiDbService)
            {
                Eegeo_DELETE m_pPoiDbService;
                m_pPoiDbService = pPoiDbService;
            }
        }
    }
}
