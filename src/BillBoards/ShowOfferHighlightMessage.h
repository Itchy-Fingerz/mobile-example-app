// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace BillBoards
    {
        class ShowOfferHighlightMessage
        {
        public:
            ShowOfferHighlightMessage(bool isOffersShownSelected)
            : m_isShowOffersSelected(isOffersShownSelected)
            {
            }
            
            bool GetSelectedOption() const
            {
                return m_isShowOffersSelected;
            }
            
        private:
            
            const bool m_isShowOffersSelected;
        };
    }
}
