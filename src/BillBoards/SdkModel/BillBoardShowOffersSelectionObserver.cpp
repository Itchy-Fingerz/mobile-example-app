// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardShowOffersSelectionObserver.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardShowOffersSelectionObserver::BillBoardShowOffersSelectionObserver(ExampleAppMessaging::TMessageBus& messageBus
                 ,View::BillBoardService& billBoardService)
            : m_showOfferSelectionCallback(this,&BillBoardShowOffersSelectionObserver::OnShowOfferSelected)
            , m_messageBus(messageBus)
            {
                m_messageBus.SubscribeNative(m_showOfferSelectionCallback);
            }
            
            BillBoardShowOffersSelectionObserver::~BillBoardShowOffersSelectionObserver()
            {
                m_messageBus.UnsubscribeNative(m_showOfferSelectionCallback);
            }
            
            void BillBoardShowOffersSelectionObserver::OnShowOfferSelected(const ShowOfferHighlightMessage &message)
            {
                m_messageBus.Publish(ExampleApp::SearchMenu::SearchMenuPerformedSearchMessage("Specialoffer", true, true));
            }
            
        }
    }
}
