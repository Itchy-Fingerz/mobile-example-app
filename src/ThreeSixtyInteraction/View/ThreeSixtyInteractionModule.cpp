// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionModule.h"
#include "ThreeSixtyInteractionViewModel.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            ThreeSixtyInteractionModule::ThreeSixtyInteractionModule(Eegeo::Helpers::IIdentityProvider& identityProvider)
            {
                m_pThreeSixtyInteractionViewModel = Eegeo_NEW(ThreeSixtyInteractionViewModel)(identityProvider.GetNextIdentity());
            }

            ThreeSixtyInteractionModule::~ThreeSixtyInteractionModule()
            {
                Eegeo_DELETE m_pThreeSixtyInteractionViewModel;
            }

            IThreeSixtyInteractionViewModel& ThreeSixtyInteractionModule::GetThreeSixtyInteractionViewModel() const
            {
                return *m_pThreeSixtyInteractionViewModel;
            }
            
            OpenableControl::View::IOpenableControlViewModel& ThreeSixtyInteractionModule::GetObservableOpenableControl() const
            {
                return m_pThreeSixtyInteractionViewModel->GetOpenableControl();
            }
        }
    }
}
