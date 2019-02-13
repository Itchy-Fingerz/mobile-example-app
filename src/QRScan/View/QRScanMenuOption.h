// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include "QRScan.h"
#include "Menu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class QRScanMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                Menu::View::IMenuViewModel& m_aboutOptionContainerMenu;
                QRScan::View::IQRScanViewModel& m_qrScanViewModel;

            public:
                QRScanMenuOption(Menu::View::IMenuViewModel& aboutOptionContainerMenu,
                                    QRScan::View::IQRScanViewModel& qrScanViewModel);

                ~QRScanMenuOption();

                void Select();
            };
        }
    }
}
