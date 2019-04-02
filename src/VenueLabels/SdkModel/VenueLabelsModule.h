// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "IVenueLabelsModule.h"
#include "PoiDb.h"
#include "IMarkerService.h"
#include "IVenueLabelsController.h"
#include "VenueLabelsChangedObserver.h"

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            class VenueLabelsModule: public IVenueLabelsModule, private Eegeo::NonCopyable
            {
            private:
                IVenueLabelsController* m_pVenueLabelsController;
                VenueLabelsChangedObserver* m_pVenueLabelsChangedObserver;
                
            public:
                VenueLabelsModule(PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider, Eegeo::Markers::IMarkerService& markerService, ExampleAppMessaging::TMessageBus& messageBus);

                ~VenueLabelsModule();
            };
        }
    }
}
