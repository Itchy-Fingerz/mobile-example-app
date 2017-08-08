// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "BillBoardService.h"
#include "ShowOfferHighlightMessage.h"


namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardShowOffersSelectionObserver
            {
            public:
                BillBoardShowOffersSelectionObserver(ExampleAppMessaging::TMessageBus& messageBus
                                                      ,View::BillBoardService& billBoardService);
                ~BillBoardShowOffersSelectionObserver();

            private:                
                Eegeo::Helpers::TCallback1<BillBoardShowOffersSelectionObserver, const ShowOfferHighlightMessage&> m_showOfferSelectionCallback;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void OnShowOfferSelected(const ShowOfferHighlightMessage &message);
            };
        }
    }
}
