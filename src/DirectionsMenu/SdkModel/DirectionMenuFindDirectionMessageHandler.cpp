// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionMenuFindDirectionMessageHandler.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            DirectionMenuFindDirectionMessageHandler::DirectionMenuFindDirectionMessageHandler(ExampleAppMessaging::TMessageBus& messageBus, Direction::SdkModel::FindDirectionQueryPerformer& findDirectionQueryPerformer)
            
            : m_messageBus(messageBus)
            , m_findDirectionQueryPerformer(findDirectionQueryPerformer)
            , m_handleFindDirectionMessageBinding(this, &DirectionMenuFindDirectionMessageHandler::OnFindDirectionMessage)
            {
                m_messageBus.SubscribeNative(m_handleFindDirectionMessageBinding);
            }
            DirectionMenuFindDirectionMessageHandler::~DirectionMenuFindDirectionMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleFindDirectionMessageBinding);
            }
            void DirectionMenuFindDirectionMessageHandler::OnFindDirectionMessage(const DirectionsMenu::DirectionMenuFindDirectionMessage& message)
            {
                m_findDirectionQueryPerformer.PerformFindDirectionQuery(message.StartLocation(),message.StartLocationLevel(),message.EndLocation(),message.EndLocationLevel(), message.IsInterior());
            }

        }
    }
}