// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanMenuOption.h"

#include "IQRScanViewModel.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanMenuOption::QRScanMenuOption(Menu::View::IMenuViewModel& aboutOptionContainerMenu,
                                                     QRScan::View::IQRScanViewModel& qrScanViewModel)
            : m_aboutOptionContainerMenu(aboutOptionContainerMenu)
            , m_qrScanViewModel(qrScanViewModel)
            {

            }

            QRScanMenuOption::~QRScanMenuOption()
            {

            }

            void QRScanMenuOption::Select()
            {
                m_aboutOptionContainerMenu.Close();
                m_qrScanViewModel.Open();
            }
        }
    }
}
