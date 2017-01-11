// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SearchResultModel.h"
#include "FindDirectionService.h"
#include "DirectionQueryResponseReceivedMessage.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

#include "RouteService.h"
#include "Route.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "RouteStyle.h"


namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            FindDirectionService::FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,Eegeo::Routes::Webservice::JsonRouteParser& resultParser,Eegeo::Routes::RouteService& routeService,Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,FindDirectionResultJsonParser& findDirectionResultParser,Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,ExampleAppMessaging::TMessageBus& messageBus)
            : m_pCurrentRequest(NULL)
            , m_findDirectionHttpRequestFactory(findDirectionHttpRequestFactory)
            , m_handleResponseCallback(this,&FindDirectionService::HandleRouteDirectionResponse)
            , m_findDirectionResultParser(findDirectionResultParser)
            , m_resultParser(resultParser)
            , m_failAlertHandler(this, &FindDirectionService::OnFailedToCallRouteResponse)
            , m_alertBoxFactory(alertBoxFactory)
            , m_messageBus(messageBus)
            , m_routeService(routeService)
            , m_pInteriorInteractionModel(interiorInteractionModel)

            {
                
            }
            FindDirectionService::~FindDirectionService()
            {
                
            }
            void FindDirectionService::InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.AddCallback(callback);
            }
            
            void FindDirectionService::RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.RemoveCallback(callback);
            }
            
            void FindDirectionService::PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery)
            {
                if(m_pCurrentRequest != NULL)
                {
                    m_pCurrentRequest->Cancel();
                }
                
                m_pCurrentRequest = m_findDirectionHttpRequestFactory.CreateFindDirectionQuery(findDirectionQuery, m_handleResponseCallback);
                m_pCurrentRequest->Dispatch();

            }
            
            void FindDirectionService::HandleRouteDirectionResponse()
            {
                Eegeo_ASSERT(m_pCurrentRequest != NULL, "Find Direction request must have been performed");
                
                if(m_pCurrentRequest->IsSucceeded())
                {
                    const std::string& response(m_pCurrentRequest->ResponseString());
                    DirectionResultModel result =  m_findDirectionResultParser.ParseGeoNamesQueryResults(response);
                     m_messageBus.Publish(DirectionResultSection::DirectionQueryResponseReceivedMessage(result));
                    
                    m_routeThicknessPolicy.SetScaleFactor(9.f);
                    m_routeThicknessPolicy.SetAltitude(100.f);

                    Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone, Eegeo::Rendering::LayerIds::AfterWorld);
                    // this will asynchronously parse the result and add the resulting route to m_routeService
                    m_resultParser.CreateRouteFromJSON(response, m_routeService, routeStyle, m_pInteriorInteractionModel);
                    
                    
                    
                    if(result.GetCode() == "Error" || result.GetRoutes().size() == 0)
                    {
                         m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                    }

                }
                else
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                }
                m_pCurrentRequest = NULL;
            }
            
            void FindDirectionService::OnFailedToCallRouteResponse()
            {
                
            }


        }
    }
}
