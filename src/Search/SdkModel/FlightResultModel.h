// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class FlightResultModel
            {
            private:
                std::string m_airlineName;
                std::string m_flightName;
                std::string m_destination;
                std::string m_gate;
                std::string m_time;
                std::string m_boardingTime;
            
            
            public:
                FlightResultModel(std::string airLineName, std::string flightName,std::string destination,std::string gate, std::string time,std::string boardingTime);
                
                const std::string GetAirLineName() const;
                const std::string GetFlight() const;
                const std::string GetFlightDestincation() const;
                const std::string GetGateNo() const;
                const std::string GetFlightTime() const;
                const std::string GetFlightBoardingTime() const;

                
            };

        }
    }
}