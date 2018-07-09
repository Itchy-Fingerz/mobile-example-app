// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SenionLabLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "IPSConfigurationParser.h"
#include "AboutPageIndoorPositionSettingsMessage.h"
#include <map>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                SenionLabLocationController::SenionLabLocationController(ISenionLabLocationManager& locationManager,
                                                                         ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                         const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                         Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                                         ExampleAppMessaging::TMessageBus& messageBus)
                : m_locationManager(locationManager)
                , m_appModeModel(appModeModel)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_appModeChangedCallback(this, &SenionLabLocationController::OnAppModeChanged)
                , m_interiorMetaDataRepository(interiorMetaDataRepository)
                , m_messageBus(messageBus)
                {
                    m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                SenionLabLocationController::~SenionLabLocationController()
                {
                    m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                void SenionLabLocationController::OnAppModeChanged()
                {
                    m_locationManager.StopUpdatingLocation();

                    typedef std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> TrackingInfoMap;

                    Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    TrackingInfoMap trackingInfoMap;
                    
                    if(interiorId.IsValid())
                    {
                        InteriorsPosition::TryAndGetInteriorTrackingInfo(trackingInfoMap, interiorId, m_interiorMetaDataRepository);
                    }
                    else
                    {
                        return;
                    }

                    if (m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
                    {
                        
                        if (interiorId.IsValid() && interiorId.Value() == "jcgroup_china_suzhou")
                        {
                            const std::string& apiKey = "17774327-e08b-44ca-899a-e5183e1b8a7c"; // map id
                            const std::string& apiSecret = "da2ed8ab-5a81-403c-a7f6-e8f16b46551a";  // customer id
                            std::map<int, std::string> floorMap;// = trackingInfo.GetFloorIndexMap(); // empty for now
                            floorMap.insert(std::make_pair(12, "0"));
                            floorMap.insert(std::make_pair(15, "1"));

                            m_locationManager.StartUpdatingLocation(apiKey, apiSecret, floorMap);
                            m_messageBus.Publish(AboutPage::AboutPageIndoorPositionSettingsMessage(apiKey,
                                        apiSecret,
                                        floorMap,
                                        ""));
                        }
                        else
                        {
                            const TrackingInfoMap::const_iterator trackingInfoEntry = trackingInfoMap.find(interiorId.Value());

                            if (trackingInfoEntry != trackingInfoMap.end())
                            {
                                const ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = trackingInfoEntry->second;
                                
                                if (trackingInfo.GetType() == "Senion")
                                {
                                            const std::string& apiKey = trackingInfo.GetConfig().GetApiKey();
                                            const std::string& apiSecret = trackingInfo.GetConfig().GetApiSecret();
                                            const std::map<int, std::string>& floorMap = trackingInfo.GetFloorIndexMap();
                                            
                                            m_locationManager.StartUpdatingLocation(apiKey, apiSecret, floorMap);
                                            m_messageBus.Publish(AboutPage::AboutPageIndoorPositionSettingsMessage(
                                                                                                                   apiKey,
                                                                                                                   apiSecret,
                                                                                                                   floorMap,
                                                                                                                   trackingInfo.GetInteriorId().Value()));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
