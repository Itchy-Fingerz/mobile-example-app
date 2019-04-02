// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "PoiDb.h"
#include "IMarkerService.h"
#include "IVenueLabelsController.h"

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            class VenueLabelsController: public IVenueLabelsController, private Eegeo::NonCopyable
            {
            private:
                PoiDb::SdkModel::PoiDbServiceProvider& m_dbServiceProvider;
                
                Eegeo::Markers::IMarkerService& m_markerService;
                std::vector<Eegeo::Markers::IMarker::IdType> m_markerIDs;
                
            public:
                VenueLabelsController(PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider, Eegeo::Markers::IMarkerService& markerService);
                
                ~VenueLabelsController();
                
                void ResetLabels(int floorIndex);
                
                void ClearLabels();
            };
        }
    }
}
