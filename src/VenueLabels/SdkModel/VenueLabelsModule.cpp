// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VenueLabelsModule.h"
#include "PoiDbService.h"
#include "PoiDbServiceProvider.h"
#include "MarkerBuilder.h"
#include "VenueLabelsController.h"

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            VenueLabelsModule::VenueLabelsModule(PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider, Eegeo::Markers::IMarkerService& markerService, ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pVenueLabelsController = Eegeo_NEW(VenueLabelsController)(serviceProvider, markerService);
                m_pVenueLabelsChangedObserver = Eegeo_NEW(VenueLabelsChangedObserver)(*m_pVenueLabelsController, messageBus);
            }

            VenueLabelsModule::~VenueLabelsModule()
            {
                Eegeo_DELETE(m_pVenueLabelsController);
                Eegeo_DELETE(m_pVenueLabelsChangedObserver);
            }
        }
    }
}
