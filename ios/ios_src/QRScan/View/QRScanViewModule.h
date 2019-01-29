// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "QRScan.h"
#include "IQRScanViewModule.h"
#include "IMetricsService.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class QRScanViewModule: public IQRScanViewModule, private Eegeo::NonCopyable
            {
            private:
                QRScanView* m_pView;
                QRScanController* m_pController;

            public:
                QRScanViewModule(IQRScanViewModel& qrScanViewModel, Metrics::IMetricsService& metricsService, ExampleAppMessaging::TMessageBus& messageBus);

                ~QRScanViewModule();

                QRScanController& GetQRScanController() const;

                QRScanView& GetQRScanView() const;
            };
        }
    }
}
