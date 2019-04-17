// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "PoiDb.h"
#include "IMarkerService.h"
#include "IVenueLabelsController.h"
#include "Interiors.h"

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
                
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                const Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
                
                void UpdateLabelVisibility(bool visible);
                
            public:
                VenueLabelsController(PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider, Eegeo::Markers::IMarkerService& markerService,const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel);
                
                ~VenueLabelsController();
                
                void ResetLabels(int floorIndex);
                
                void ClearLabels();
                
                void Update(float dt);
                
            };
        }
    }
}
