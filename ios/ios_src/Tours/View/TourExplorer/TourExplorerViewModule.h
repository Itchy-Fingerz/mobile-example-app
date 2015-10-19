// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "TourExplorerViewIncludes.h"
#include "Rendering.h"
#include "Tours.h"
#include "ITourExplorerViewModule.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "TourExplorerViewController.h"
#include "ITourHovercardView.h"

@class ImageStore;

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class TourExplorerViewModule: public ITourExplorerViewModule, private Eegeo::NonCopyable
                {
                private:
                    TourExplorerView* m_pView;
                    TourExplorerViewController* m_pViewController;
                    
                public:
                    TourExplorerViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                           ITourExplorerViewModel& viewModel,
                                           TourHovercard::ITourHovercardView& tourHoverCardView,
                                           ITourExplorerCompositeViewController& tourExplorerCompositeViewController,
                                           const Eegeo::Rendering::ScreenProperties& screenProperties,
                                           Metrics::IMetricsService& metricsService,
                                           ImageStore* pImageStore);
                    
                    ~TourExplorerViewModule();
                    
                    TourExplorerView& GetTourExplorerView() const;
                };
            }
        }
    }
}
