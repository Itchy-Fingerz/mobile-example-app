// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FindDirectionServiceModule.h"


namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            FindDirectionServiceModule::FindDirectionServiceModule(Eegeo::Concurrency::Tasks::IWorkPool& workPool,Eegeo::Routes::RouteService& routeService,Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                                   Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,                          Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                                   const std::string& eegeoApiKey,ExampleAppMessaging::TMessageBus& messageBus)
            :m_workPool(workPool)
            ,m_routeService(routeService)
            ,m_pInteriorInteractionModel(interiorInteractionModel)
            {
                m_pDirectionResultJsonParser = Eegeo_NEW(FindDirectionResultJsonParser)();
                m_pDirectionHttpRequestFactory = Eegeo_NEW(FindDirectionHttpRequestFactory)(eegeoApiKey,webRequestFactory,urlEncoder);
                m_resultParser = Eegeo_NEW(Eegeo::Routes::Webservice::JsonRouteParser)(m_workPool);

                m_pDirectionService = Eegeo_NEW(FindDirectionService)(*m_pDirectionHttpRequestFactory,*m_resultParser,m_routeService,m_pInteriorInteractionModel,*m_pDirectionResultJsonParser,alertBoxFactory,messageBus);
                m_pDirectionQueryPerformer = Eegeo_NEW(FindDirectionQueryPerformer)(GetFindDirectionService());
                
                //m_routeThicknessPolicy.SetScaleFactor(1.0f);
//                Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone, Eegeo::Rendering::LayerIds::InteriorEntities);
                

            }

            FindDirectionServiceModule::~FindDirectionServiceModule()
            {
                Eegeo_DELETE m_pDirectionResultJsonParser;
                Eegeo_DELETE m_pDirectionHttpRequestFactory;
                Eegeo_DELETE m_pDirectionService;
                Eegeo_DELETE m_resultParser;
                
            }
            
            FindDirectionService& FindDirectionServiceModule::GetFindDirectionService() const
            {
                return *m_pDirectionService;
            }
            
            FindDirectionQueryPerformer& FindDirectionServiceModule::GetFindDirectionQueryPerformer() const
            {
                return *m_pDirectionQueryPerformer;
            }

            Eegeo::Concurrency::Tasks::IWorkPool& FindDirectionServiceModule::GetWorkPool() const
            {
                return m_workPool;
            }
            Eegeo::Routes::RouteService& FindDirectionServiceModule::GetRouteService() const
            {
                return m_routeService;
            }

        }
    }
}