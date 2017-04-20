// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace SdkModel
        {
            const std::string DefaultEegeoCustomAlertId = "eegeo";
            
            class CustomAlertModel
            {
            public:
                CustomAlertModel()
                : m_id(DefaultEegeoCustomAlertId)
                {
                    
                }
                
                std::string GetId() const { return m_id; }
                void SetId(const std::string& newId) { m_id = newId; }
            private:
                std::string m_id;
            };
        }
    }
}
