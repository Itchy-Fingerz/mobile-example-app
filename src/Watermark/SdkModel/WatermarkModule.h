// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Watermark.h"
#include "IWatermarkModule.h"
#include "IIdentity.h"
#include "WatermarkViewModel.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            class WatermarkModule : public IWatermarkModule, private Eegeo::NonCopyable
            {
            private:
                WatermarkModel* m_pWatermarkModel;
                View::WatermarkViewModel* m_pViewModel;
                View::WatermarkDataRepository* m_pWatermarkDataRepository;
                View::WatermarkDataFactory* m_pWatermarkDataFactory;
                SdkModel::WatermarkInteriorStateChangedObserver* m_pWatermarkInteriorStateChangedObserver;
                
            public:
                WatermarkModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                const std::string& appName,
                                const std::string& googleAnalyticsReferrerToken,
                                Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                ExampleAppMessaging::TMessageBus& messageBus,
                                ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus);
                
                ~WatermarkModule();
                
                WatermarkModel& GetWatermarkModel() const;
                
                View::IWatermarkViewModel& GetWatermarkViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
                
                View::IWatermarkDataRepository& GetWatermarkDataRepository() const;
                
                View::IWatermarkDataFactory& GetWatermarkDataFactory() const;
                
                void AddThirdPartyWatermarkData();
            };
        }
    }
}
