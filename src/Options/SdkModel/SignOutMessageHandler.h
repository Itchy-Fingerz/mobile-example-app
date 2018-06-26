// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SignOutMessage.h"
#include "PersistentSettings.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class SignOutMessageHandler : private Eegeo::NonCopyable
            {
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SignOutMessageHandler, const SignOutMessage&> m_messageHandlerBinding;
                PersistentSettings::IPersistentSettingsModel& m_persistentSettings;

                void OnSignedOut(const SignOutMessage& message);
                
            public:
                SignOutMessageHandler(ExampleAppMessaging::TMessageBus& messageBus, PersistentSettings::IPersistentSettingsModel& persistentSettings);
                
                ~SignOutMessageHandler();
            };
        }
    }
}
