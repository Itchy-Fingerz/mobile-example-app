// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "IQRScanMenuModule.h"
#include "QRScan.h"
#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "IMetricsService.h"
#include "Menu.h"
#include "Reaction.h"
#include "Search.h"
#include "Types.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace SdkModel
        {
            class QRScanMenuModule: public IQRScanMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pQRScanMenuModel;
                Menu::View::IMenuOptionsModel* m_pQRScanMenuOptionsModel;

            public:
                QRScanMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                   QRScan::View::IQRScanViewModel& qrScanViewModel);

                ~QRScanMenuModule();

                Menu::View::IMenuModel& GetQRScanMenuModel() const;
            };
        }
    }
}
