// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "DeepLinkModule.h"
#include "DeepLinkModel.h"
#include "DeepLinkController.h"
#include "ICameraTransitionController.h"
#include "IAlertBoxFactory.h"
#include "IWebLoadRequestFactory.h"
#include "DeepLinkLocationHandler.h"
#include "DeepLinkConfigHandler.h"
#include "CoverageTrees.h"
#include "CityThemes.h"

namespace {
    const char * const LOCATION_PATH = "location";
    const char * const MYMAP_PATH = "mapscene";
    const bool CONFIG_DEEP_LINK_ENABLED = true;
}

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            ExampleApp::DeepLink::SdkModel::DeepLinkModule::DeepLinkModule(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                           Eegeo::Web::IWebLoadRequestFactory& webFactory,
                                                                           Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory, ApplicationConfig::ApplicationConfiguration& defaultConfig,
                                                                           Eegeo::Streaming::CoverageTrees::ICoverageTreeManifestLoader& manifestLoader,
                                                                           Eegeo::Streaming::CoverageTrees::CoverageTreeManifestNotifier& manifestNotifier,
                                                                           Eegeo::Resources::CityThemes::CityThemeLoader& cityThemeLoader,
                                                                           Eegeo::Resources::CityThemes::ICityThemesService& cityThemeService,
                                                                           Search::SdkModel::InteriorMenuObserver& interiorMenuObserver,
                                                                           Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                           AboutPage::View::IAboutPageViewModel& aboutPageViewModule,
                                                                           Eegeo::Location::NavigationService& navigationService,
                                                                           Eegeo::Web::ApiTokenService& apiTokenService,
                                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                           const ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel)
            {
                m_pDeepLinkModel = Eegeo_NEW(DeepLinkModel)();
                DeepLinkLocationHandler* locationHandler = Eegeo_NEW(DeepLinkLocationHandler)(cameraTransitionController, alertBoxFactory);
                m_pDeepLinkModel->AddRoute(LOCATION_PATH, locationHandler);
                
                if(CONFIG_DEEP_LINK_ENABLED)
                {
                    DeepLinkConfigHandler* configHandler= Eegeo_NEW(DeepLinkConfigHandler)(cameraTransitionController,
                    webFactory,
                    alertBoxFactory,
                    defaultConfig,
                    manifestLoader,
                    manifestNotifier,
                    cityThemeLoader,
                    cityThemeService,
                    interiorMenuObserver,
                    searchQueryPerformer,
                    aboutPageViewModule,
                    navigationService,
                    apiTokenService,
                    interiorSelectionModel,
                    appModeModel);

                    m_pDeepLinkModel->AddRoute(MYMAP_PATH, configHandler);
                }
                
                m_pDeepLinkController = Eegeo_NEW(DeepLinkController)(*m_pDeepLinkModel);
            }
            
            ExampleApp::DeepLink::SdkModel::DeepLinkModule::~DeepLinkModule()
            {
                Eegeo_DELETE(m_pDeepLinkModel);
                Eegeo_DELETE(m_pDeepLinkController);
            }
            
            ExampleApp::DeepLink::SdkModel::DeepLinkController& ExampleApp::DeepLink::SdkModel::DeepLinkModule::GetDeepLinkController()
            {
                return *m_pDeepLinkController;
            }
        }
    }
}
