// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IIdentity.h"
#include "ThreeSixtyInteraction.h"
#include "IThreeSixtyInteractionModule.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class ThreeSixtyInteractionModule : public IThreeSixtyInteractionModule, private Eegeo::NonCopyable
            {
                IThreeSixtyInteractionViewModel* m_pThreeSixtyInteractionViewModel;

            public:
                ThreeSixtyInteractionModule(Eegeo::Helpers::IIdentityProvider& identityProvider);

                ~ThreeSixtyInteractionModule();

                IThreeSixtyInteractionViewModel& GetThreeSixtyInteractionViewModel() const;
                
                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;

            };
        }
    }
}
