// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorId.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardModel
            {
            public:
                BillBoardModel();
                ~BillBoardModel();                
                
                void SetInteriorId(const Eegeo::Resources::Interiors::InteriorId& building);
                const Eegeo::Resources::Interiors::InteriorId& GetInteriorId();
                void SetFloor(int floor);
                int GetFloor();
                void SetPosition(const Eegeo::Space::LatLong& position);
                const Eegeo::Space::LatLong& GetPosition();
                void SetTargetPosition(const Eegeo::Space::LatLong& target);
                
            private:
                Eegeo::Resources::Interiors::InteriorId m_building;
                int m_floor;
                Eegeo::Space::LatLong m_currentLatLong;
                
            };
        }
    }
}
