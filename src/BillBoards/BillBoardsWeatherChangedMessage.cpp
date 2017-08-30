// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardsWeatherChangedMessage.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        BillBoardsWeatherChangedMessage::BillBoardsWeatherChangedMessage(const WeatherMenu::SdkModel::WeatherMenuStateModel& weatherStateModel)
            : m_weatherStateModel(weatherStateModel)
        {
        }

        const WeatherMenu::SdkModel::WeatherMenuStateModel& BillBoardsWeatherChangedMessage::Model() const
        {
            return m_weatherStateModel;
        }
    }
}
