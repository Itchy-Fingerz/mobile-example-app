// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "InteriorExplorerState.h"
#include "AppCamera.h"
#include "Interiors.h"
#include "Streaming.h"
#include "ICallback.h"
#include "InteriorsExplorer.h"
#include "PersistentSettings.h"
#include "IIndoorMapEntityInformationService.h"
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
                                                
                        AppModes::States::SdkModel::InteriorExplorerState& m_parentState;
                        
                        const float m_maxTimeout;
                        float m_timeUntilTimeout;
                        bool m_hasFailed;
                        
                        Eegeo::IndoorMapEntityInformation::IIndoorMapEntityInformationService& m_indoorMapEntityInformationService;
                        Eegeo::IndoorMapEntityInformation::IndoorMapEntityInformationModelId m_indoorMapEntityInforamtionModelId;
                        
                    public:
                        
                        InteriorExplorerStreamState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                    const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                    Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                    InteriorsExplorerModel& interiorsExplorerModel,
                                                    Eegeo::IndoorMapEntityInformation::IIndoorMapEntityInformationService& indoorMapEntityInformationService,
                                                    const int streamingResourceWebTimeOutInSecond);
                        
                        ~InteriorExplorerStreamState();
                        
                        void Enter(int previousState);
                        
                        void Update(float dt);
                        
                        void Exit(int nextState);
                        
                        bool HasModelLoaded();

                    };
            }
        }
    }
}
