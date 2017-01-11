// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "FindDirectionService.h"
#include "FindDirectionQueryPerformer.h"
#include "FindDirectionResultJsonParser.h"
#include "FindDirectionHttpRequestFactory.h"
#include "AlertBox.h"
#include "IWorkPool.h"
#include "RouteService.h"
#include "Route.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "EegeoWorld.h"
#include "JsonRouteParser.h"
#include "RouteStyle.h"
#include "InteriorInteractionModel.h"




namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionServiceModule
            {
            public:
                FindDirectionServiceModule(Eegeo::Concurrency::Tasks::IWorkPool& workPool,Eegeo::Routes::RouteService& routeService,Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel
,Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                    Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,                          Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                    const std::string& eegeoApiKey,
                                           ExampleAppMessaging::TMessageBus& messageBus);
                ~FindDirectionServiceModule();
                FindDirectionService& GetFindDirectionService() const;
                FindDirectionQueryPerformer& GetFindDirectionQueryPerformer() const;
                Eegeo::Concurrency::Tasks::IWorkPool& GetWorkPool() const;
                Eegeo::Routes::RouteService& GetRouteService() const;

            private:
                Eegeo::Routes::RouteService& m_routeService;
                Eegeo::Concurrency::Tasks::IWorkPool& m_workPool;
                Eegeo::Routes::Webservice::JsonRouteParser* m_resultParser;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_pInteriorInteractionModel;

                //Eegeo::Routes::Style::Thickness::LinearAltitudeBasedRouteThicknessPolicy m_routeThicknessPolicy;
                FindDirectionService* m_pDirectionService;
                FindDirectionResultJsonParser* m_pDirectionResultJsonParser;
                FindDirectionHttpRequestFactory* m_pDirectionHttpRequestFactory;
                FindDirectionQueryPerformer* m_pDirectionQueryPerformer;
                
                
            };
        }
    }
}