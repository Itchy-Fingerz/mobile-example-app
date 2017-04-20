// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomAlertModule.h"
#include "CustomAlertViewModel.h"
#include "CustomAlertModel.h"
#include "CustomAlertInteriorStateChangedObserver.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace SdkModel
        {
            CustomAlertModule::CustomAlertModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                             const std::string& appName,
                                             const std::string& googleAnalyticsReferrerToken,
                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                             Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                             InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                             ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pViewModel = Eegeo_NEW(View::CustomAlertViewModel)(identityProvider.GetNextIdentity(), false);
                
                
                
        
                
//                m_pCustomAlertInteriorStateChangedObserver = Eegeo_NEW(CustomAlertInteriorStateChangedObserver)(*m_pCustomAlertModel,
//                                                                                                            interiorSelectionModel,
//                                                                                                            interiorsModelRepository,
//                                                                                                            interiorsExplorerModel);
            }
            
            CustomAlertModule::~CustomAlertModule()
            {
                //Eegeo_DELETE m_pCustomAlertInteriorStateChangedObserver;
                Eegeo_DELETE m_pCustomAlertModel;
                Eegeo_DELETE m_pViewModel;
            }
            
            View::ICustomAlertViewModel& CustomAlertModule::GetCustomAlertViewModel() const
            {
                return *m_pViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& CustomAlertModule::GetScreenControlViewModel() const
            {
                return m_pViewModel->GetScreenControlViewModel();
            }
            
 
        }
    }
}
