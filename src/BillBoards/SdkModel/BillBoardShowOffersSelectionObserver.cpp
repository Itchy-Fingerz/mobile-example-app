// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardShowOffersSelectionObserver.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardShowOffersSelectionObserver::BillBoardShowOffersSelectionObserver(View::BillBoardService& billBoardService,PathDrawing::SdkModel::WayPointOnMapModel &wayPointModel,Direction::SdkModel::FindDirectionService &findDirectionService, Menu::View::IMenuViewModel& directionViewModel,ExampleAppMessaging::TMessageBus& messageBus)
            : m_showOfferSelectionCallback(this,&BillBoardShowOffersSelectionObserver::OnShowOfferSelected)
            , m_directionsMenuStateChangedCallback(this,&BillBoardShowOffersSelectionObserver::OnDirectionMenuStateChanged)
            , m_wayPointModel(wayPointModel)
            , isSpecialOffersModeOn(false)
            , m_messageBus(messageBus)
            , m_findDirectionService(findDirectionService)
            , m_directionViewModel(directionViewModel)
            , m_billBoardService(billBoardService)
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
                    m_findDirectionService.HideAllRoutes();
                    m_billBoardService.ShowSpecialOfferBillBoardsOnly();
                    // Add condition here to check the current state of Directions menu
                    
                    m_messageBus.Publish(ExampleApp::SearchMenu::SearchMenuPerformedSearchMessage("offers", true, true));
                    if(m_directionViewModel.IsFullyOpen())
                    {
                        m_messageBus.Publish(DirectionsMenuInitiation::DirectionsMenuStateChangedMessage(ExampleApp::DirectionsMenuInitiation::Active,false,true));
                    }
                }
            }
         
            void BillBoardShowOffersSelectionObserver::OnDirectionMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage &message)
            {
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Active && isSpecialOffersModeOn && !message.GetSpecialOffersFlag())
                {
                    isSpecialOffersModeOn = false;
                    m_wayPointModel.ShowAllWayPoints();
                    m_findDirectionService.ShowLastRequestRoutes();
                }
            }
        }
    }
}
