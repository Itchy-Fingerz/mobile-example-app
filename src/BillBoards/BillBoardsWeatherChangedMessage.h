// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WeatherMenuStateModel.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        class BillBoardsWeatherChangedMessage
        {
            WeatherMenu::SdkModel::WeatherMenuStateModel m_weatherStateModel;

        public:
            BillBoardsWeatherChangedMessage(const WeatherMenu::SdkModel::WeatherMenuStateModel& weatherStateModel);

            const WeatherMenu::SdkModel::WeatherMenuStateModel& Model() const;
        };
    }
}

