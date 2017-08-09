// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardShowOffersSelectionObserver.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardShowOffersSelectionObserver::BillBoardShowOffersSelectionObserver(ExampleAppMessaging::TMessageBus& messageBus,View::BillBoardService& billBoardService,PathDrawing::SdkModel::WayPointOnMapModel &wayPointModel)
            : m_showOfferSelectionCallback(this,&BillBoardShowOffersSelectionObserver::OnShowOfferSelected)
            , m_directionsMenuStateChangedCallback(this,&BillBoardShowOffersSelectionObserver::OnDirectionMenuStateChanged)
            , m_wayPointModel(wayPointModel)
            , isSpecialOffersModeOn(false)
            , m_messageBus(messageBus)
            {
                m_messageBus.SubscribeNative(m_showOfferSelectionCallback);
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            BillBoardShowOffersSelectionObserver::~BillBoardShowOffersSelectionObserver()
            {
                m_messageBus.UnsubscribeNative(m_showOfferSelectionCallback);
                m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            void BillBoardShowOffersSelectionObserver::OnShowOfferSelected(const ShowOfferHighlightMessage &message)
            {
                if(message.GetSelectedOption())
                {
                    isSpecialOffersModeOn = true;
                    m_wayPointModel.HideAllWayPoints();
                    m_messageBus.Publish(ExampleApp::SearchMenu::SearchMenuPerformedSearchMessage("Specialoffer", true, true));
                }
            }
         
            void BillBoardShowOffersSelectionObserver::OnDirectionMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage &message)
            {
                if(isSpecialOffersModeOn)
                {
                    isSpecialOffersModeOn = false;
                    m_wayPointModel.ShowAllWayPoints();
                }
            }
        }
    }
}
