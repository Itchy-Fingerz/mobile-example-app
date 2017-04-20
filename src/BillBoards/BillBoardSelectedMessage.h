// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace BillBoards
    {
        class BillBoardSelectedMessage
        {
        public:
            BillBoardSelectedMessage(std::string poiID)
            : m_poiID(poiID)
            {
            }
            
            std::string GetPoiId() const { return m_poiID; }
            
        private:
            const std::string m_poiID;
        };
    }
}
