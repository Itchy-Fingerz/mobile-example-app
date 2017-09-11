// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "EegeoSearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoSearchResultModel::EegeoSearchResultModel()
                : m_phone("")
                , m_webUrl("")
                , m_imageUrl("")
                , m_address("")
                , m_description("")
                , m_facebookUrl("")
                , m_twitterUrl("")
                , m_email("")
                , m_customViewUrl("")
                , m_customViewHeight(-1)
                {
                }
                
                EegeoSearchResultModel::EegeoSearchResultModel(const std::string& phone,
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
                                                               const int& customViewHeight)
                    : m_phone(phone)
                    , m_webUrl(webUrl)
                    , m_imageUrl(imageUrl)
                    , m_address(address)
                    , m_description(description)
                    , m_facebookUrl(facebookUrl)
                    , m_twitterUrl(twitterUrl)
                    , m_email(email)
                    , m_customViewUrl(customViewUrl)
                    , m_customViewDayUrl(customViewDayUrl)
                    , m_customViewNightUrl(customViewNightUrl)
                    , m_customViewDawnUrl(customViewDawnUrl)
                    , m_customViewDuskUrl(customViewDuskUrl)
                    , m_customViewHeight(customViewHeight)
                {
                }

                EegeoSearchResultModel::~EegeoSearchResultModel()
                {

                }
                
                const std::string& EegeoSearchResultModel::GetDescription() const
                {
                    return m_description;
                }
                
                const std::string& EegeoSearchResultModel::GetAddress() const
                {
                    return m_address;
                }

                const std::string& EegeoSearchResultModel::GetPhone() const
                {
                    return m_phone;
                }

                const std::string& EegeoSearchResultModel::GetWebUrl() const
                {
                    return m_webUrl;
                }
                
                const std::string& EegeoSearchResultModel::GetFacebookUrl() const
                {
                    return m_facebookUrl;
                }
                
                const std::string& EegeoSearchResultModel::GetTwitterUrl() const
                {
                    return m_twitterUrl;
                }
                
                const std::string& EegeoSearchResultModel::GetEmail() const
                {
                    return m_email;
                }
                
                bool EegeoSearchResultModel::HasImage() const
                {
                    return !m_imageUrl.empty();
                }
                
                const std::string& EegeoSearchResultModel::GetImageUrl() const
                {
                    return m_imageUrl;
                }
                
                const std::string& EegeoSearchResultModel::GetCustomViewUrl() const
                {
                    return m_customViewUrl;
                }
                
                const std::string& EegeoSearchResultModel::GetCustomViewDayUrl() const
                {
                    return m_customViewDayUrl;
                }
                
                const std::string& EegeoSearchResultModel::GetCustomViewNightUrl() const
                {
                    return m_customViewNightUrl;
                }
                
                const std::string& EegeoSearchResultModel::GetCustomViewDawnUrl() const
                {
                    return m_customViewDawnUrl;
                }
                
                const std::string& EegeoSearchResultModel::GetCustomViewDuskUrl() const
                {
                    return m_customViewDuskUrl;
                }
                
                const int& EegeoSearchResultModel::GetCustomViewHeight() const
                {
                    return m_customViewHeight;
                }
            }
        }
    }
}
