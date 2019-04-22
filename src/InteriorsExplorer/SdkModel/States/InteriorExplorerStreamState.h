// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "InteriorExplorerState.h"
#include "AppCamera.h"
#include "Interiors.h"
#include "Streaming.h"
#include "ICallback.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                
                    class InteriorExplorerStreamState : public Helpers::IStateMachineState
                    {
                    private:
                        
                        const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                        Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                        InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                        InteriorsExplorerModel& m_interiorsExplorerModel;
                        
                        Eegeo::Resources::Interiors::InteriorsCellResourceObserver& m_interiorsCellResourceObserver;
                        Eegeo::Helpers::TCallback1<InteriorExplorerStreamState, const Eegeo::Resources::Interiors::InteriorsCellResource> m_interiorCellAddedHandler;
                        
                        AppModes::States::SdkModel::InteriorExplorerState& m_parentState;
                        
                        const float m_maxTimeout;
                        float m_timeUntilTimeout;
                        bool m_hasFailed;
                        bool m_hasInitialInteriorPartLoaded;
                        bool m_hasInteriorsFullyLoaded;
                        
                        void OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& callback);
                    public:
                        
                        InteriorExplorerStreamState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                    const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                    Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                    InteriorsExplorerModel& interiorsExplorerModel,
                                                    Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver);
                        
                        ~InteriorExplorerStreamState();
                        
                        void Enter(int previousState);
                        
                        void Update(float dt);
                        
                        void Exit(int nextState);
                    };
            }
        }
    }
}
