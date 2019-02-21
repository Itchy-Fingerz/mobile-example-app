// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanMenuModule.h"

#include "QRScanMenuOption.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuViewModel.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace SdkModel
        {
            QRScanMenuModule::QRScanMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                                   QRScan::View::IQRScanViewModel& qrScanViewModel)
            {

                m_pQRScanMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pQRScanMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pQRScanMenuModel);
                m_pQRScanMenuOptionsModel->AddItem("QR Code Location", "QR Code Location", "", "", Eegeo_NEW(View::QRScanMenuOption)(menuViewModel, qrScanViewModel));
            }

            QRScanMenuModule::~QRScanMenuModule()
            {
                Eegeo_DELETE m_pQRScanMenuOptionsModel;
                Eegeo_DELETE m_pQRScanMenuModel;
            }

            Menu::View::IMenuModel& QRScanMenuModule::GetQRScanMenuModel() const
            {
                return *m_pQRScanMenuModel;
            }
        }
    }
}
