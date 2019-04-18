// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VenueLabelsController.h"
#include "PoiDbService.h"
#include "PoiDbServiceProvider.h"
#include "SearchResultModel.h"
#include "MarkerBuilder.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"
#include "ICameraTransitionController.h"
#include "CameraTransitionController.h"
#include "InteriorsExplorer.h"
#include "InteriorsModel.h"

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            VenueLabelsController::VenueLabelsController(PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider, Eegeo::Markers::IMarkerService& markerService,const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
            : m_dbServiceProvider(serviceProvider)
            , m_markerService(markerService)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorTransitionModel(interiorTransitionModel)
            , m_cameraTransitionController(cameraTransitionController)
            {
            }

            VenueLabelsController::~VenueLabelsController()
            {
            }
            
            void VenueLabelsController::ResetLabels(int floorIndex)
            {
                ClearLabels();
                
                std::vector<Search::SdkModel::SearchResultModel> outPutResults;
                if(m_dbServiceProvider.IsPoiDbServiceStarted()) {
                    ExampleApp::PoiDb::SdkModel::IPoiDbService* service = NULL;
                    m_dbServiceProvider.TryGetService(service);
                    if(service != NULL)
                    {
                        service->FetchVenuesLabelsWithQuery(outPutResults);                        
                    }
                }
                
                for(std::vector<Search::SdkModel::SearchResultModel>::iterator it = outPutResults.begin(); it != outPutResults.end(); ++it)
                {
                    Search::SdkModel::SearchResultModel searchResult = *it;
                
                    const auto& markerCreateParams = Eegeo::Markers::MarkerBuilder()
                    .SetLocation(searchResult.GetLocation().GetLatitudeInDegrees(), searchResult.GetLocation().GetLongitudeInDegrees())
                    .SetLabelIcon(searchResult.GetIconKey())
                    .SetLabelText(searchResult.GetTitle())
                    .SetElevation(searchResult.GetHeightAboveTerrainMetres())
                    .SetInteriorWithFloorIndex(searchResult.GetBuildingId().Value(), searchResult.GetFloor())
                    .SetLabelStyle("place_name_venue")
                    .SetSubPriority(0)
                    .Build();
                    
                    const Eegeo::Markers::IMarker::IdType markerId = m_markerService.Create(markerCreateParams);
                    m_markerIDs.push_back(markerId);
                }
                
            }

            void VenueLabelsController::ClearLabels()
            {
                while(!m_markerIDs.empty())
                {
                    m_markerService.Destroy(m_markerIDs.back());
                    m_markerIDs.pop_back();
                }
            }
            
            void VenueLabelsController::Update(float dt)
            {
                const bool showingInterior = m_interiorTransitionModel.InteriorIsVisible();
                const bool canShowInteriorPins = m_interiorInteractionModel.IsCollapsed();
                
                if (showingInterior && canShowInteriorPins)
                {
                    UpdateLabelVisibility(false);
                }
                else
                {
                    UpdateLabelVisibility(true);
                }

            }
            void VenueLabelsController::UpdateLabelVisibility(bool visible)
            {
                for(std::vector<Eegeo::Markers::IMarker::IdType>::iterator it = m_markerIDs.begin(); it != m_markerIDs.end(); ++it)
                {
                    Eegeo::Markers::IMarker::IdType markerID = *it;
                    
                    Eegeo::Markers::IMarker &marker = m_markerService.Get(markerID);
                    
                    marker.SetHidden(visible);
                }
            }
            
            bool VenueLabelsController::IsVenueLabel(Eegeo::Markers::IMarker::IdType pickedMarkerId)
            {
                for(std::vector<Eegeo::Markers::IMarker::IdType>::iterator it = m_markerIDs.begin(); it != m_markerIDs.end(); ++it)
                {
                    Eegeo::Markers::IMarker::IdType markerID = *it;
                    if (markerID == pickedMarkerId)
                    {
                        return true;
                    }
                }
                return false;
            }
            
            bool VenueLabelsController::HandleTouchTap(const Eegeo::v2& screenTapPoint)
            {
                auto pickedMarkerId = Eegeo::Markers::IMarker::InvalidId;
                if (m_markerService.TryPick(screenTapPoint, pickedMarkerId) && IsVenueLabel(pickedMarkerId))
                {
                    const Eegeo::Space::LatLong& location = m_markerService.Get(pickedMarkerId).GetAnchorLocation().GetLatLong();
                    const Eegeo::dv3& newInterestPoint = location.ToECEF();
                    float distanceFromInterest = InteriorsExplorer::DefaultInteriorSearchResultTransitionInterestDistance;
                m_cameraTransitionController.StartTransitionTo(newInterestPoint,distanceFromInterest,m_interiorInteractionModel.GetInteriorModel()->GetId(),m_interiorInteractionModel.GetFloorParam());
                    
                    return true;
                }
                
                return false;
            }
        }
    }
}
