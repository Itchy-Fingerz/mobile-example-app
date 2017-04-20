// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include <string>
#include "VideoAssetReaderService.h"

namespace ExampleApp
{
    namespace VideoAssetReader
    {
        class VideoAssetReaderModule : private Eegeo::NonCopyable
        {
            
        private:
            VideoAssetReaderService *m_pVideoReaderService;
            
        public:
            VideoAssetReaderModule(ExampleAppMessaging::TMessageBus& messageBus);
            ~VideoAssetReaderModule();
            
            VideoAssetReaderService &GetVideoAssetReaderService()
            {
                return *m_pVideoReaderService;
            }
            
        };
    }
    
}
