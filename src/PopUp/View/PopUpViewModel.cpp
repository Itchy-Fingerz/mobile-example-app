// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PopUpViewModel.h"

#include <sstream>
#include <iomanip>

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            PopUpViewModel::PopUpViewModel()
            {
            }

            PopUpViewModel::~PopUpViewModel()
            {                
            }
            
            void PopUpViewModel::Open(double xPosition, double yPosition)
            {
                m_openedCallbacks.ExecuteCallbacks(xPosition, yPosition);
            }

            void PopUpViewModel::Close()
            {
                m_closedCallbacks.ExecuteCallbacks();
            }

            void PopUpViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback2<double, double>& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void PopUpViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback2<double, double>& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void PopUpViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void PopUpViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
            
        }
    }
}
