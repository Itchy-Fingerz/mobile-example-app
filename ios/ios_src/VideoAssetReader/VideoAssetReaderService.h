// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <string>
#include <AVFoundation/AVFoundation.h>

#include "Types.h"
#include "URLRequestedMessage.h"
#include "DeeplinkURLRequestedMessage.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "LinkOutObserver.h"
#include "AVPlayerStateObserver.h"
#include "VideoAssetReaderState.h"

namespace ExampleApp
{
    namespace VideoAssetReader
    {
        void StillImageDataReleaseCallback(void *releaseRefCon, const void *baseAddress);
        void GPUImageCreateResizedSampleBuffer(CVPixelBufferRef cameraFrame, CGSize finalSize, CMSampleBufferRef *sampleBuffer);
        
        class VideoAssetReaderService : private Eegeo::NonCopyable
        {
        private:
            AVPlayer *m_pPlayer;
            AVPlayerItemVideoOutput *m_pVideoOutput;
            
            CVOpenGLESTextureCacheRef m_videoTextureCache;
            dispatch_queue_t m_videoOutputQueue;
            GLuint m_renderedVideoTexture;
            
            AVPlayerStateObserver *m_pPlayerObserver;
            
            int m_lastPausedTime;
            VideoAssetReaderState *m_pCurrentVideoAssetReaderState;
            
        public:
            VideoAssetReaderService(ExampleAppMessaging::TMessageBus& messageBus);
            ~VideoAssetReaderService();
            
            void StartReading(std::string fileName);
            GLuint GetRenderedtexture();
            
            void AvailableDuration();
            void RenderVideoBillBoard();
            void ResetPlayer();
            void PausePlayer();
            void ContinueAfterPause();
            
            bool IsVideoEnded();
//            bool GetIsPausedByUserFlagStatus() { return m_isPausedByUser; }
//            bool GetIsPausedForBufferingFlagStatus(){ return m_isPausedForBuffering; }
//            bool GetHasStartedPlayingFlagStatus(){ return m_hasStartedPlaying; }
            
            bool GetIsPausedByUserFlagStatus() { if( m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_PAUSED_BY_USER)
                    return true;
                else if (m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_PAUSED_BY_USER_IN_BUFFERING)
                    return true;
                return false;}
            bool GetIsPausedForBufferingFlagStatus(){ return  m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_PAUSED_FOR_BUFFERING ? true : false; }
            bool GetHasStartedPlayingFlagStatus(){ return  m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_STOPPED ? false : true; }


        };
    }
}
