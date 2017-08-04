// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "Types.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorSelectionController : private Eegeo::NonCopyable
            {
            public:
                
                InteriorSelectionController(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                            InteriorsExplorerModel& interiorExplorerModel,
                                            InteriorExplorerUserInteractionModel& userInteractionModel,
                                            const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerModelRepository,
                                            Eegeo::Resources::Interiors::InteriorsCameraController& cameraController);
                
                virtual ~InteriorSelectionController();
                
            private:
                void OnInteriorSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                void OnInteriorSelected(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                void OnInteriorsUserInteractionEnabled();
                
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& m_interiorMarkerModelRepository;
                Eegeo::Resources::Interiors::InteriorsCameraController& m_cameraController;
                InteriorExplorerUserInteractionModel& m_userInteractionModel;
                
                Eegeo::Helpers::TCallback1<InteriorSelectionController, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionChangedHandler;
                Eegeo::Helpers::TCallback0<InteriorSelectionController> m_interiorsUserInteractionEnabledHandler;
                InteriorsExplorerModel& m_interiorExplorerModel;
            };
        }
    }
}
