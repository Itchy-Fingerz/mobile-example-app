// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardWeatherStateChangedObserver.h"
#include "WeatherSelectedMessage.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardWeatherStateChangedObserver::BillBoardWeatherStateChangedObserver(ExampleAppMessaging::TMessageBus& messageBus
                 ,View::BillBoardService& billBoardService)
            : m_messageBus(messageBus)
            , m_billBoardService(billBoardService)
            , m_weatherChangedCallback(this, &BillBoardWeatherStateChangedObserver::OnWeatherStateChanged)
            {
                m_messageBus.SubscribeNative(m_weatherChangedCallback);
            }
            
            BillBoardWeatherStateChangedObserver::~BillBoardWeatherStateChangedObserver()
            {
                m_messageBus.UnsubscribeNative(m_weatherChangedCallback);
            }
            
            void BillBoardWeatherStateChangedObserver::OnWeatherStateChanged(const WeatherMenu::WeatherSelectedMessage& message)
            {
                
                if(message.Model().HasTimeState())
                    m_billBoardService.SetDayTime(message.Model().GetTimeState());
                if(message.Model().HasWeatherState())
                    m_billBoardService.SetWeather(message.Model().GetWeatherState());
                if(message.Model().HasSeasonState())
                    m_billBoardService.SetSeason(message.Model().GetSeasonState());
                
                m_billBoardService.OnWeatherStateChange();
                
            }
            
        }
    }
}
