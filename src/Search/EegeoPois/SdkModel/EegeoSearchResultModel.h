// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "InteriorId.h"
#include "LatLongAltitude.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoSearchResultModel
                {
                    std::string m_phone;
                    std::string m_webUrl;
                    std::string m_imageUrl;
                    std::string m_address;
                    std::string m_description;
                    std::string m_facebookUrl;
                    std::string m_twitterUrl;
                    std::string m_email;
                    std::string m_customViewUrl;
                    std::string m_customViewDayUrl;
                    std::string m_customViewNightUrl;
                    std::string m_customViewDawnUrl;
                    std::string m_customViewDuskUrl;
                    int m_customViewHeight;
                    
                public:
                    
                    EegeoSearchResultModel(const std::string& phone,
                                           const std::string& webUrl,
                                           const std::string& address,
                                           const std::string& description,
                                           const std::string& imageUrl,
                                           const std::string& facebookUrl,
                                           const std::string& twitterUrl,
                                           const std::string& email,
                                           const std::string& customViewUrl,
                                           const std::string& customViewDayUrl,
                                           const std::string& customViewNightUrl,
                                           const std::string& customViewDawnUrl,
                                           const std::string& customViewDuskUrl,
                                           const int& customViewHeight);
                    
                    EegeoSearchResultModel();
                    
                    ~EegeoSearchResultModel();
                    
                    const std::string& GetPhone() const;

                    const std::string& GetWebUrl() const;
                    
                    const std::string& GetAddress() const;
                    
                    const std::string& GetDescription() const;
                    
                    const std::string& GetFacebookUrl() const;
                    
                    const std::string& GetTwitterUrl() const;
                    
                    const std::string& GetEmail() const;
                    
                    bool HasImage() const;
                    
                    const std::string& GetImageUrl() const;
                    
                    const std::string& GetCustomViewUrl() const;
                    
                    const std::string& GetCustomViewDayUrl() const;

                    const std::string& GetCustomViewNightUrl() const;

                    const std::string& GetCustomViewDawnUrl() const;

                    const std::string& GetCustomViewDuskUrl() const;
                    
                    const int& GetCustomViewHeight() const;
                };
            }
        }
    }
}
