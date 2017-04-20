// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlightResultModel.h"
namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            FlightResultModel::FlightResultModel(std::string airLineName, std::string flightName,std::string destination,std::string gate, std::string time,std::string boardingTime)
            : m_airlineName(airLineName)
            , m_flightName(flightName)
            , m_destination(destination)
            , m_gate(gate)
            , m_time(time)
            , m_boardingTime(boardingTime)
            {
            
            }
            
            
            const std::string FlightResultModel::GetAirLineName() const
            {
                return m_airlineName;
            }
            
            const std::string FlightResultModel::GetFlight() const
            {
                return m_flightName;
            }
            const std::string FlightResultModel::GetFlightDestincation() const
            {
                return m_destination;
            }
            
            const std::string FlightResultModel::GetGateNo() const
            {
                return m_gate;
            }
            const std::string FlightResultModel::GetFlightTime() const
            {
                return m_time;
            }
            const std::string FlightResultModel::GetFlightBoardingTime() const
            {
                return m_boardingTime;
            }

        }
    }
}