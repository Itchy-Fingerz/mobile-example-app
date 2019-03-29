// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionViewModel.h"

#include <sstream>
#include <iomanip>

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            ThreeSixtyInteractionViewModel::ThreeSixtyInteractionViewModel(Eegeo::Helpers::TIdentity identity)
            : m_openable(identity)
            {
            }

            ThreeSixtyInteractionViewModel::~ThreeSixtyInteractionViewModel()
            {                
            }
            
            bool ThreeSixtyInteractionViewModel::IsOpen() const
            {
                return m_openable.IsOpen();
            }
            void ThreeSixtyInteractionViewModel::Open(std::string url)
            {
                if(!IsOpen())
                {
                    m_openable.Open();
                    m_openedCallbacks.ExecuteCallbacks(url);
                }
            }

            void ThreeSixtyInteractionViewModel::Close()
            {
                if(IsOpen())
                {
                    m_openable.Close();
                    m_closedCallbacks.ExecuteCallbacks();
                }
            }
            
            OpenableControl::View::IOpenableControlViewModel& ThreeSixtyInteractionViewModel::GetOpenableControl()
            {
                return m_openable;
            }
            
            void ThreeSixtyInteractionViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback1<std::string&>& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void ThreeSixtyInteractionViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback1<std::string&>& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void ThreeSixtyInteractionViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void ThreeSixtyInteractionViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
            
        }
    }
}
