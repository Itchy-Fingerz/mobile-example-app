// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VenueLabelsController.h"
#include "PoiDbService.h"
#include "PoiDbServiceProvider.h"
#include "SearchResultModel.h"
#include "MarkerBuilder.h"

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            VenueLabelsController::VenueLabelsController(PoiDb::SdkModel::PoiDbServiceProvider &serviceProvider, Eegeo::Markers::IMarkerService& markerService)
            : m_dbServiceProvider(serviceProvider)
            , m_markerService(markerService)
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
        }
    }
}
