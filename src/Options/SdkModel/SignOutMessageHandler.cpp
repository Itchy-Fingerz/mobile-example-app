// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SignOutMessageHandler.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            SignOutMessageHandler::SignOutMessageHandler(ExampleAppMessaging::TMessageBus& messageBus, PersistentSettings::IPersistentSettingsModel& persistentSettings)
            : m_messageBus(messageBus)
            , m_messageHandlerBinding(this, &SignOutMessageHandler::OnSignedOut)
            , m_persistentSettings(persistentSettings)
            {
                m_messageBus.SubscribeNative(m_messageHandlerBinding);
            }

            SignOutMessageHandler::~SignOutMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_messageHandlerBinding);
            }
            
            void SignOutMessageHandler::OnSignedOut(const ExampleApp::Options::SignOutMessage &message)
            {
                m_persistentSettings.ClearValidationPersistentState();
            }
        }
    }
}
