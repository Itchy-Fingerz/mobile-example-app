// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "BillBoardService.h"
#include "WeatherSelectedMessage.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardWeatherStateChangedObserver
            {
            public:
                BillBoardWeatherStateChangedObserver(ExampleAppMessaging::TMessageBus& messageBus
                                                      ,View::BillBoardService& billBoardService);
                ~BillBoardWeatherStateChangedObserver();

            private:                

                Eegeo::Helpers::TCallback1<BillBoardWeatherStateChangedObserver, const WeatherMenu::WeatherSelectedMessage&> m_weatherChangedCallback;
                
                View::BillBoardService& m_billBoardService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void OnWeatherStateChanged(const WeatherMenu::WeatherSelectedMessage& message);
            };
        }
    }
}
