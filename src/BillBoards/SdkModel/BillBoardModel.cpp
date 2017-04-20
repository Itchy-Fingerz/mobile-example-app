// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardModel.h"

namespace ExampleApp
{
    namespace BillBoards
    {

        namespace SdkModel
        {
            BillBoardModel::BillBoardModel()
            : m_building("")
            , m_floor(0)
            , m_currentLatLong(0.0f,0.0f)
            {            
            }
            
            BillBoardModel::~BillBoardModel()
            {
            
            }
            
            void BillBoardModel::SetInteriorId(const Eegeo::Resources::Interiors::InteriorId& building)
            {
                m_building = building;
            }
            
            const Eegeo::Resources::Interiors::InteriorId& BillBoardModel::GetInteriorId()
            {
                return m_building;
            }
            
            void BillBoardModel::SetFloor(int floor)
            {
                m_floor = floor;
            }
            
            int BillBoardModel::GetFloor()
            {
                return m_floor;
            }
            
            void BillBoardModel::SetPosition(const Eegeo::Space::LatLong& position)
            {
                m_currentLatLong = position;
            }
            
            const Eegeo::Space::LatLong& BillBoardModel::GetPosition()
            {
                return m_currentLatLong;
            }
        }
    }
}
