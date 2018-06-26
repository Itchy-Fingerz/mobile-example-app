// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Options.h"
#include "IOptionsModule.h"
#include "OptionsViewModel.h"
#include "IIdentity.h"
#include "OptionsSdkIncludes.h"
#include "BidirectionalBus.h"
#include "IHttpCache.h"
#include "NetIncludes.h"
#include "CompletedCacheClearMessageHandler.h"
#include "PersistentSettings.h"

namespace ExampleApp
{
    namespace Options
    {
        class OptionsModule : public IOptionsModule, private Eegeo::NonCopyable
        {
            View::OptionsViewModel* m_pOptionsViewModel;
            SdkModel::StreamOverWifiOnlyChangedMessageHandler* m_pStreamOverWifiOnlyChangedMessageHandler;
            SdkModel::CacheEnabledChangedMessageHandler* m_pCacheEnabledChangedMessageHandler;
            View::CompletedCacheClearMessageHandler* m_pCompletedCacheClearMessageHandler;
            SdkModel::SignOutMessageHandler* m_pSignOutMessageHandler;
            
        public:
            OptionsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                          ExampleAppMessaging::TMessageBus& messageBus,
                          Net::SdkModel::INetworkCapabilities& networkCapabilities,
                          PersistentSettings::IPersistentSettingsModel& persistentSettings);
            
            ~OptionsModule();
            
            View::IOptionsViewModel& GetOptionsViewModel() const;
            
            OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
        };
    }
}
