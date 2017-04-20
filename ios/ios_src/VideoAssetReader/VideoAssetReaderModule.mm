// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VideoAssetReaderModule.h"


namespace ExampleApp
{
    namespace VideoAssetReader
    {
        
        VideoAssetReaderModule::VideoAssetReaderModule(ExampleAppMessaging::TMessageBus& messageBus)
        {
            m_pVideoReaderService = Eegeo_NEW(ExampleApp::VideoAssetReader::VideoAssetReaderService)(messageBus);
        }
        
        VideoAssetReaderModule::~VideoAssetReaderModule()
        {
            Eegeo_DELETE(m_pVideoReaderService);
        }
        
    }
}
