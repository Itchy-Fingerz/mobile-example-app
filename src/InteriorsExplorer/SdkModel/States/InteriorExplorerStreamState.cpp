// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerStreamState.h"
#include "IAppCameraController.h"
#include "CameraFrustumStreamingVolume.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorInteractionModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsCellResourceObserver.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                namespace
                {
                    const float DelayForShowingStreamingDialogSeconds = 1.0f;
                }
                
                InteriorExplorerStreamState::InteriorExplorerStreamState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                                         const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                         Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                                         InteriorsExplorerModel& interiorsExplorerModel,                                                     Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver)
                : m_parentState(parentState)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                , m_interiorsExplorerModel(interiorsExplorerModel)
                , m_interiorCellAddedHandler(this, &InteriorExplorerStreamState::OnInteriorAddedToSceneGraph)
                , m_maxTimeout(60.0f)
                , m_hasFailed(false)
                , m_interiorsCellResourceObserver(interiorsCellResourceObserver)
                , m_hasInitialInteriorPartLoaded(false)
                , m_hasInteriorsFullyLoaded(false)
                {
                    m_interiorsCellResourceObserver.RegisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);
                }
                
                InteriorExplorerStreamState::~InteriorExplorerStreamState()
                {
                    m_interiorsCellResourceObserver.UnregisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);
                }
                
                void InteriorExplorerStreamState::Enter(int previousState)
                {
                    m_hasFailed = false;
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(true);
                    
                    m_timeUntilTimeout = m_maxTimeout;
                }
                
                void InteriorExplorerStreamState::OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& resource)
                {
                    if (m_hasInitialInteriorPartLoaded) {
                        if (m_interiorInteractionModel.HasInteriorModel())
                        {
                            m_hasInteriorsFullyLoaded = true;
                        }
                    }
                    else
                    {
                        if (m_interiorInteractionModel.HasInteriorModel())
                        {
                            m_hasInitialInteriorPartLoaded = true;
                        }
                    }                    
                }
                
                void InteriorExplorerStreamState::Update(float dt)
                {
                    m_timeUntilTimeout -= dt;
                    
                    if(!m_interiorsExplorerModel.GetInteriorStreamingDialogVisibility() &&
                       (m_maxTimeout - m_timeUntilTimeout) >= DelayForShowingStreamingDialogSeconds)
                    {
                        m_interiorsExplorerModel.ShowInteriorStreamingDialog();
                    }
                    
                    if(m_timeUntilTimeout <= 0.0f && !m_hasFailed)
                    {
                        m_hasFailed = true;
                        m_parentState.SetLastEntryAttemptSuccessful(false);
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::Exit);
                        m_parentState.ShowFailMessage();
                        return;
                    }
                    
                    if (m_interiorInteractionModel.HasInteriorModel() && m_hasInteriorsFullyLoaded)
                    {
                        m_parentState.SetLastEntryAttemptSuccessful(true);
                        m_interiorVisibilityUpdater.SetInteriorShouldDisplay(true);
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::View);
                    }
                }
                
                void InteriorExplorerStreamState::Exit(int nextState)
                {
                    m_interiorsExplorerModel.HideInteriorStreamingDialog(m_parentState.GetLastEntryAttemptSuccessful());
                }
            }
        }
    }
}
