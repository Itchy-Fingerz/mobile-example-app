// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CustomAlert.h"
#include "Interiors.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace SdkModel
        {
            class CustomAlertInteriorStateChangedObserver
            {
            public:
                CustomAlertInteriorStateChangedObserver(CustomAlertModel& customAlertModel,
                                                      Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                      Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                      InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel);
                
                ~CustomAlertInteriorStateChangedObserver();
                
            private:
                CustomAlertModel& m_customAlertModel;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                
                void OnInteriorExplorerEntered();
                Eegeo::Helpers::TCallback0<CustomAlertInteriorStateChangedObserver> m_interiorExplorerEnteredCallback;
                
                void OnInteriorExplorerExit();
                Eegeo::Helpers::TCallback0<CustomAlertInteriorStateChangedObserver> m_interiorExplorerExitCallback;
            };
        }

    }
}
