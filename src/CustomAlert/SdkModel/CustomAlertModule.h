// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CustomAlert.h"
#include "ICustomAlertModule.h"
#include "IIdentity.h"
#include "CustomAlertViewModel.h"
#include "BidirectionalBus.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace SdkModel
        {
            class CustomAlertModule : public ICustomAlertModule, private Eegeo::NonCopyable
            {
            private:
                CustomAlertModel* m_pCustomAlertModel;
                View::CustomAlertViewModel* m_pViewModel;
                SdkModel::CustomAlertInteriorStateChangedObserver* m_pCustomAlertInteriorStateChangedObserver;
                
            public:
                CustomAlertModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                const std::string& appName,
                                const std::string& googleAnalyticsReferrerToken,
                                Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                ExampleAppMessaging::TMessageBus& messageBus);
                
                ~CustomAlertModule();
                
                CustomAlertModel& GetCustomAlertModel() const;
                
                View::ICustomAlertViewModel& GetCustomAlertViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
                
                
                
            };
        }
    }
}
