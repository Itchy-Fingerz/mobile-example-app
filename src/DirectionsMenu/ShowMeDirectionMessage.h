// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        class ShowMeDirectionMessage
        {
        public:
            ShowMeDirectionMessage(Search::SdkModel::SearchResultModel endLocationModel);
            
            ShowMeDirectionMessage(Search::SdkModel::SearchResultModel startLocationModel,Search::SdkModel::SearchResultModel endLocationModel);

            ~ShowMeDirectionMessage();
                        
            Search::SdkModel::SearchResultModel GetStartLocationModel() const;
            Search::SdkModel::SearchResultModel GetEndLocationModel() const;
            const bool HasStartLocation()const;
            
        private:
            Search::SdkModel::SearchResultModel m_startLocationModel;
            Search::SdkModel::SearchResultModel m_endLocationModel;
            bool m_hasStartLocation;
        };
    }
}
