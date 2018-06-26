// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsModule.h"
#include "OptionsViewModel.h"
#include "StreamOverWifiOnlyChangedMessageHandler.h"
#include "CacheEnabledChangedMessageHandler.h"
#include "INetworkCapabilities.h"
#include "SignOutMessageHandler.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace Options
    {
        OptionsModule::OptionsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                     ExampleAppMessaging::TMessageBus& messageBus,
                                     Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                     PersistentSettings::IPersistentSettingsModel& persistentSettings)
        {
            m_pOptionsViewModel = Eegeo_NEW(View::OptionsViewModel)(identityProvider.GetNextIdentity(),
                                                                    networkCapabilities.StreamOverWifiOnly(),
                                                                    networkCapabilities.HttpCachingEnabled());
            
            m_pStreamOverWifiOnlyChangedMessageHandler = Eegeo_NEW(SdkModel::StreamOverWifiOnlyChangedMessageHandler)(messageBus,
                                                                                                                      networkCapabilities);
            
            m_pCacheEnabledChangedMessageHandler = Eegeo_NEW(SdkModel::CacheEnabledChangedMessageHandler)(networkCapabilities,
                                                                                                          messageBus);
            
            m_pCompletedCacheClearMessageHandler = Eegeo_NEW(View::CompletedCacheClearMessageHandler)(*m_pOptionsViewModel,
                                                                                                      messageBus);

            m_pSignOutMessageHandler = Eegeo_NEW(SdkModel::SignOutMessageHandler)(messageBus,
                                                                                  persistentSettings);
        }
        
        OptionsModule::~OptionsModule()
        {
            Eegeo_DELETE m_pCompletedCacheClearMessageHandler;
            Eegeo_DELETE m_pCacheEnabledChangedMessageHandler;
            Eegeo_DELETE m_pStreamOverWifiOnlyChangedMessageHandler;
            Eegeo_DELETE m_pOptionsViewModel;
            Eegeo_DELETE m_pSignOutMessageHandler;
        }
        
        View::IOptionsViewModel& OptionsModule::GetOptionsViewModel() const
        {
            return *m_pOptionsViewModel;
        }
        
        OpenableControl::View::IOpenableControlViewModel& OptionsModule::GetObservableOpenableControl() const
        {
            return m_pOptionsViewModel->GetOpenableControl();
        }
    }
}
