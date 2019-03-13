// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteractionModelStateChangedMessage
        {
        public:
            InteractionModelStateChangedMessage(bool interiorVisible,
                                                int selectedFloorIndex,
                                                const std::string& selectedFloorName,
                                                Eegeo::Resources::Interiors::InteriorId interiorId)
            : m_interiorVisible(interiorVisible)
            , m_selectedFloorIndex(selectedFloorIndex)
            , m_selectedFloorName(selectedFloorName)
            , m_interiorId(interiorId)
            {
            }
            
            bool IsInteriorVisible() const { return m_interiorVisible; }
            int GetSelectedFloorIndex() const { return m_selectedFloorIndex; }
            std::string GetSelectedFloorName() const { return m_selectedFloorName; }
            Eegeo::Resources::Interiors::InteriorId GetInteriorID() const { return m_interiorId;}
        private:
            const bool m_interiorVisible;
            const int m_selectedFloorIndex;
            const std::string m_selectedFloorName;
            const Eegeo::Resources::Interiors::InteriorId m_interiorId;
        };
    }
}
