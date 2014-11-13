// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WeatherSelectedMessageHandler.h"

namespace ExampleApp
{
	namespace WeatherMenu
	{
		void WeatherSelectedMessageHandler::HandleReceivedWeatherSelectedMessage(const WeatherSelectedMessage& message)
		{
			const WeatherMenuStateModel& model = message.Model();

			if(model.HasTimeState())
			{
				m_weatherController.SetTime(model.GetTimeState());
			}
			if(model.HasWeatherState())
			{
				m_weatherController.SetWeather(model.GetWeatherState());
			}
			if(model.HasSeasonState())
			{
				m_weatherController.SetSeason(model.GetSeasonState());
			}

			m_weatherController.Refresh();
		}

		WeatherSelectedMessageHandler::WeatherSelectedMessageHandler(
			IWeatherController& weatherController,
			ExampleAppMessaging::UiToNativeMessageBus& messageBus)
			: m_weatherController(weatherController)
			, m_messageBus(messageBus)
			, m_handlerBinding(this, &WeatherSelectedMessageHandler::HandleReceivedWeatherSelectedMessage)
		{
			m_messageBus.Subscribe(m_handlerBinding);
		}

		WeatherSelectedMessageHandler::~WeatherSelectedMessageHandler()
		{
			m_messageBus.Unsubscribe(m_handlerBinding);
		}
	}
}
