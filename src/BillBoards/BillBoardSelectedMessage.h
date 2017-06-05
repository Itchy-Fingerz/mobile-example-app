// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace BillBoards
    {
        class BillBoardSelectedMessage
        {
        public:
            BillBoardSelectedMessage(std::string poiID, std::string uniqueTag)
            : m_poiID(poiID),
                m_uniqueTag(uniqueTag)
            {
            }
            
            std::string GetPoiId() const { return m_poiID; }
            std::string GetUniqueTag() const { return m_uniqueTag; }
            
        private:
            const std::string m_poiID;
            const std::string m_uniqueTag;
        };
    }
}
