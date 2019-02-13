// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanViewModel.h"

#include <sstream>
#include <iomanip>

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanViewModel::QRScanViewModel(
                Eegeo::Helpers::TIdentity identity,
                const std::string& buildVersion,
                const std::string& platformVersion,
                const std::string& platformHash,
                const std::string& platformArchitecture,
                const std::string& aboutText,
                const std::string& appName)
                : m_openable(identity)
                , m_buildVersion(buildVersion)
                , m_platformVersion(platformVersion)
                , m_platformHash(platformHash)
                , m_platformArchitecture(platformArchitecture)
                , m_aboutText(aboutText)
                , m_appName(appName)
                , m_indoorPositioningType("")
            {
                
            }

            QRScanViewModel::~QRScanViewModel()
            {
                
            }


            bool QRScanViewModel::IsOpen() const
            {
                return m_openable.IsOpen();
            }

            const std::string QRScanViewModel::GetContent(bool showHiddenContent) const
            {
                std::stringstream content;
                
                content << m_aboutText
                        << "\n\nApplication build version: " + m_buildVersion
                        << "\n\nPlatform version: " + m_platformVersion
                        << "\nPlatform hash:\n" + m_platformHash
                        << "\nPlatform runtime arch: " + m_platformArchitecture
                        << "\nApplication Name: " + m_appName
                        << m_indoorPositioningType
                        << "\n";
                
                if(m_indoorPositioningType == "\nIndoor positioning type: Senion" && showHiddenContent)
                {
                    content << "\n eeGeo Floor number: " << m_eegeoFloorIndex
                            << "\n Senion Floor number: " << m_senionFloorNumber
                            << "\n Latitude: " << std::setprecision(10) << m_latitude
                            << "\n Longitude: " << m_longitude
                            << "\n ApiKey: " << m_apiKey
                            << "\n ApiSecret: " << m_apiSecret
                            << "\n FloorMap: " << m_floorMapString.str()
                            << "\n InteriorId: " << m_interiorId
                            << "\n";
                }
                else if(m_indoorPositioningType == "\nIndoor positioning type: IndoorAtlas" && showHiddenContent)
                {
                    content << "\n eeGeo Floor number: " << m_eegeoFloorIndex
                            << "\n IndoorAtlas Floor id: " << m_indoorAtlasFloorId
                            << "\n Latitude: " << std::setprecision(10) << m_latitude
                            << "\n Longitude: " << m_longitude
                            << "\n ApiKey: " << m_apiKey
                            << "\n ApiSecret: " << m_apiSecret
                            << "\n FloorMap: " << m_floorMapString.str()
                            << "\n InteriorId: " << m_interiorId
                            << "\n";
                }
                
                return content.str();
            }

            void QRScanViewModel::Open()
            {
                if(!IsOpen())
                {
                    m_openable.Open();
                    m_openedCallbacks.ExecuteCallbacks();
                }
            }

            void QRScanViewModel::Close()
            {
                if(IsOpen())
                {
                    m_openable.Close();
                    m_closedCallbacks.ExecuteCallbacks();
                }
            }
            
            void QRScanViewModel::UpdateApplicationName(const std::string& appName)
            {
                m_appName = appName;
            }
            
            OpenableControl::View::IOpenableControlViewModel& QRScanViewModel::GetOpenableControl()
            {
                return m_openable;
            }

            void QRScanViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void QRScanViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void QRScanViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void QRScanViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
            
            void QRScanViewModel::SetIndoorPositioningType(const std::string& indoorPositioningType)
            {
                m_indoorPositioningType = indoorPositioningType;
            }
            
            void QRScanViewModel::SetSenionData(const int32_t& eegeoFloorNumber,
                                                   const int& senionFloorNumber,
                                                   const double& latitude,
                                                   const double& longitude)
            {
                m_eegeoFloorIndex = eegeoFloorNumber;
                m_senionFloorNumber = senionFloorNumber;
                m_latitude = latitude;
                m_longitude = longitude;
            }

            void QRScanViewModel::SetIndoorAtlasData(const int &eegeoFloorindex,
                                                        const std::string &indoorAtlasFloorId,
                                                        const double &latitude,
                                                        const double &longitude)
            {
                m_eegeoFloorIndex = eegeoFloorindex;
                m_indoorAtlasFloorId = indoorAtlasFloorId;
                m_latitude = latitude;
                m_longitude = longitude;
            }

            void QRScanViewModel::SetIndoorPositionSettings(const std::string& apiKey,
                                                               const std::string& apiSecret,
                                                               const std::map<int, std::string>& floorMap,
                                                               const std::string& interiorId)
            {
                m_apiKey = apiKey;
                m_apiSecret = apiSecret;
                m_floorMap = floorMap;
                m_interiorId = interiorId;
                
                std::map<int, std::string> map = floorMap;

                m_floorMapString.str(std::string());
                for(std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
                {
                    m_floorMapString << it->second << "\n";
                }
            }
        }
    }
}
