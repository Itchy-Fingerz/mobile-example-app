// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ShowMeDirectionMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {

        ShowMeDirectionMessage::ShowMeDirectionMessage(Search::SdkModel::SearchResultModel endLocation)
        : m_endLocationModel(endLocation)
        , m_hasStartLocation(false)
        {
        
        }
        ShowMeDirectionMessage::ShowMeDirectionMessage(Search::SdkModel::SearchResultModel startLocationModel,Search::SdkModel::SearchResultModel endLocationModel)
        : m_startLocationModel(startLocationModel)
        , m_endLocationModel(endLocationModel)
        , m_hasStartLocation(true)
        {
            
        }
        ShowMeDirectionMessage::~ShowMeDirectionMessage()
        {
        
        }
        
        Search::SdkModel::SearchResultModel ShowMeDirectionMessage::GetStartLocationModel() const
        {
            return m_startLocationModel;
        }
        
        Search::SdkModel::SearchResultModel ShowMeDirectionMessage::GetEndLocationModel() const
        {
            return m_endLocationModel;
        }
        
        const bool ShowMeDirectionMessage::HasStartLocation()const
        {
            return m_hasStartLocation;
        }

        
    }
}
