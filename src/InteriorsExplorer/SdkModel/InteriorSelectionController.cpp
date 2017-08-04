// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorSelectionController.h"
#include "InteriorSelectionModel.h"
#include "InteriorMarkerModelRepository.h"
#include "InteriorsCameraController.h"
#include "InteriorMarkerModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorExplorerUserInteractionModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorSelectionController::InteriorSelectionController(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                     InteriorsExplorerModel& interiorExplorerModel,
                                                                     InteriorExplorerUserInteractionModel& userInteractionModel,
                                                                     const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerModelRepository,
                                                                     Eegeo::Resources::Interiors::InteriorsCameraController& cameraController)
            : m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorExplorerModel(interiorExplorerModel)
            , m_interiorMarkerModelRepository(interiorMarkerModelRepository)
            , m_cameraController(cameraController)
            , m_interiorSelectionChangedHandler(this, &InteriorSelectionController::OnInteriorSelectionChanged)
            , m_interiorsUserInteractionEnabledHandler(this,&InteriorSelectionController::OnInteriorsUserInteractionEnabled)
            , m_userInteractionModel(userInteractionModel)
            {
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionChangedHandler);
                m_userInteractionModel.InsertEnabledChangedCallback(m_interiorsUserInteractionEnabledHandler);
            }
            
            InteriorSelectionController::~InteriorSelectionController()
            {
                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionChangedHandler);
                m_userInteractionModel.RemoveEnabledChangedCallback(m_interiorsUserInteractionEnabledHandler);
            }
            
            
            void InteriorSelectionController::OnInteriorSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                if (m_interiorSelectionModel.IsInteriorSelected())
                {
                    OnInteriorSelected(interiorId);
                }
            }
            
            void InteriorSelectionController::OnInteriorSelected(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                if (!m_interiorMarkerModelRepository.Contains(interiorId))
                {
                    return;
                }
                
                const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& interiorMarkerModel = m_interiorMarkerModelRepository.Get(interiorId);
                
                const Eegeo::dv3& ecefInterestPoint = interiorMarkerModel.GetMarkerLatLongAltitude().ToECEF();

                m_cameraController.SetInterestLocation(ecefInterestPoint);
                m_cameraController.SetDistanceToInterest(InteriorsExplorer::DefaultInteriorTransitionInterestDistance);
                
            }
            
            void InteriorSelectionController::OnInteriorsUserInteractionEnabled()
            {
                
                if(m_interiorSelectionModel.GetSelectedInteriorId().Value() == "98a265e2-b890-4c6b-a28f-948c92e36914")  // NOTE: Hard Coded condition for LAX initial floor
                {
                    
                    m_interiorExplorerModel.SelectFloor(1);

                    const Eegeo::dv3& ecefInterestPoint = Eegeo::Space::LatLongAltitude::FromDegrees(33.9433384, -118.4091894, 0).ToECEF();

                    m_cameraController.SetInterestLocation(ecefInterestPoint);
                    m_cameraController.SetDistanceToInterest(InteriorsExplorer::DefaultInteriorTransitionInterestDistance * 2);
                }
                
            }

        }
    }
}
