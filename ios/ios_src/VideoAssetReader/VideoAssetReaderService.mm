// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VideoAssetReaderService.h"


namespace ExampleApp
{
    namespace VideoAssetReader
    {
        # define ONE_FRAME_DURATION 0.03
        
        
        void StillImageDataReleaseCallback(void *releaseRefCon, const void *baseAddress)
        {
            free((void *)baseAddress);
        }
        
        void GPUImageCreateResizedSampleBuffer(CVPixelBufferRef cameraFrame, CGSize finalSize, CMSampleBufferRef *sampleBuffer)
        {
            
            CGSize originalSize = CGSizeMake(CVPixelBufferGetWidth(cameraFrame), CVPixelBufferGetHeight(cameraFrame));
            
            CVPixelBufferLockBaseAddress(cameraFrame, 0);
            GLubyte *sourceImageBytes =  (GLubyte *)CVPixelBufferGetBaseAddress(cameraFrame);
            CGDataProviderRef dataProvider = CGDataProviderCreateWithData(NULL, sourceImageBytes, CVPixelBufferGetBytesPerRow(cameraFrame) * originalSize.height, NULL);
            CGColorSpaceRef genericRGBColorspace = CGColorSpaceCreateDeviceRGB();
            CGImageRef cgImageFromBytes = CGImageCreate((int)originalSize.width, (int)originalSize.height, 8, 32, CVPixelBufferGetBytesPerRow(cameraFrame), genericRGBColorspace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst, dataProvider, NULL, NO, kCGRenderingIntentDefault);
            
            GLubyte *imageData = (GLubyte *) calloc(1, (int)finalSize.width * (int)finalSize.height * 4);
            
            CGContextRef imageContext = CGBitmapContextCreate(imageData, (int)finalSize.width, (int)finalSize.height, 8, (int)finalSize.width * 4, genericRGBColorspace,  kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
            
            CGContextDrawImage(imageContext, CGRectMake(0.0, 0.0, finalSize.width, finalSize.height), cgImageFromBytes);
            
            CGImageRelease(cgImageFromBytes);
            CGContextRelease(imageContext);
            CGColorSpaceRelease(genericRGBColorspace);
            CGDataProviderRelease(dataProvider);
            
            CVPixelBufferRef pixel_buffer = NULL;
            CVPixelBufferCreateWithBytes(kCFAllocatorDefault, finalSize.width, finalSize.height, kCVPixelFormatType_32BGRA, imageData, finalSize.width * 4, StillImageDataReleaseCallback, NULL, NULL, &pixel_buffer);
            CMVideoFormatDescriptionRef videoInfo = NULL;
            CMVideoFormatDescriptionCreateForImageBuffer(NULL, pixel_buffer, &videoInfo);
            
            CMTime frameTime = CMTimeMake(1, 30);
            CMSampleTimingInfo timing = {frameTime, frameTime, kCMTimeInvalid};
            
            CMSampleBufferCreateForImageBuffer(kCFAllocatorDefault, pixel_buffer, YES, NULL, NULL, videoInfo, &timing, sampleBuffer);
            CVPixelBufferUnlockBaseAddress(cameraFrame, 0);
            
            CFRelease(videoInfo);
            CVPixelBufferRelease(pixel_buffer);
        }
        
        VideoAssetReaderService::VideoAssetReaderService(ExampleAppMessaging::TMessageBus& messageBus) :
        m_pPlayer(NULL),
        m_videoTextureCache(NULL)
        {
            m_lastPausedTime = 0;
            m_pCurrentVideoAssetReaderState = Eegeo_NEW(VideoAssetReaderState);
        }
        
        VideoAssetReaderService::~VideoAssetReaderService()
        {
            [m_pPlayerObserver release];
            m_pPlayerObserver = nil;
            
            [m_pPlayer.currentItem removeOutput:m_pVideoOutput];
            [m_pPlayer release];
            m_pPlayer = nil;
            
            [m_pVideoOutput release];
            m_videoOutputQueue = nil;
            
            m_videoTextureCache = NULL;
            
            dispatch_release(m_videoOutputQueue);
            
            m_renderedVideoTexture = NULL;
            
            m_pCurrentVideoAssetReaderState = NULL;
            
            
        }
        
        void VideoAssetReaderService::ResetPlayer()
        {
            if(m_pPlayer)
            {
                m_pCurrentVideoAssetReaderState->SetCurrentPlayerState(PLAYER_STATE_STOPPED);
                
                [m_pPlayer.currentItem removeOutput:m_pVideoOutput];
                [m_pPlayer pause];
                [m_pPlayer release];
                m_pPlayer = nil;
                
                [m_pVideoOutput release];
                m_pVideoOutput = nil;
                
                CFRelease(m_videoOutputQueue);
                m_videoOutputQueue = nil;
                
                if(m_renderedVideoTexture)
                {
                    glDeleteTextures(1, &m_renderedVideoTexture);
                    m_renderedVideoTexture = NULL;
                }
                
                CFRelease(m_videoTextureCache);
                m_videoTextureCache = nil;
                
            }
        }
        
        void VideoAssetReaderService::PausePlayer()
        {
            if(m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_STOPPED)
            {
                m_pCurrentVideoAssetReaderState->SetCurrentPlayerState(PLAYER_STATE_PAUSED_BY_USER_IN_BUFFERING);
            }
            else
            {
                m_pCurrentVideoAssetReaderState->SetCurrentPlayerState(PLAYER_STATE_PAUSED_BY_USER);
            }
            [m_pPlayer pause];
        }
        
        void VideoAssetReaderService::ContinueAfterPause()
        {
            if(m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() != PLAYER_STATE_PAUSED_BY_USER_IN_BUFFERING)
            {
                m_pCurrentVideoAssetReaderState->SetCurrentPlayerState(PLAYER_STATE_PLAYING);
                [m_pPlayer play];
            }
            else
            {
                [[m_pPlayer currentItem] addOutput:m_pVideoOutput];
                [m_pVideoOutput requestNotificationOfMediaDataChangeWithAdvanceInterval:ONE_FRAME_DURATION];
                m_pCurrentVideoAssetReaderState->SetCurrentPlayerState(PLAYER_STATE_PLAYING);
                [m_pPlayer play];
            }
        }
        
        void VideoAssetReaderService::StartReading(std::string fileName)
        {
            ResetPlayer();
            
            if (!m_videoTextureCache) {
                CVReturn err = CVOpenGLESTextureCacheCreate(kCFAllocatorDefault, NULL,[EAGLContext currentContext], NULL, &m_videoTextureCache);
                if (err != noErr) {
                    NSLog(@"Error at CVOpenGLESTextureCacheCreate %d", err);
                }
            }
            
            m_pPlayer = [[AVPlayer alloc] init];
            m_pPlayerObserver = [[[AVPlayerStateObserver alloc] initWithPlayer:m_pPlayer] retain];
            m_pPlayer.currentItem.canUseNetworkResourcesForLiveStreamingWhilePaused = YES;
            
            NSDictionary *pixBuffAttributes = @{(id)kCVPixelBufferPixelFormatTypeKey: @(kCVPixelFormatType_32BGRA)};
            m_pVideoOutput = [[AVPlayerItemVideoOutput alloc] initWithPixelBufferAttributes:pixBuffAttributes];
            m_videoOutputQueue = dispatch_queue_create("myVideoOutputQueue", DISPATCH_QUEUE_SERIAL);
            [m_pVideoOutput setDelegate:m_pPlayerObserver queue:m_videoOutputQueue];
            
            [[m_pPlayer currentItem] removeOutput:m_pVideoOutput];
            
            AVPlayerItem *item = [AVPlayerItem playerItemWithURL:[NSURL URLWithString:[NSString stringWithCString:fileName.c_str() encoding:NSUTF8StringEncoding]]];
            
            AVAsset *asset = [item asset];
            
            [asset loadValuesAsynchronouslyForKeys:@[@"tracks"] completionHandler:^{
                
                NSError *error;
                
                if ([asset statusOfValueForKey:@"tracks" error:nil] == AVKeyValueStatusLoaded) {
                    NSArray *tracks = [asset tracksWithMediaType:AVMediaTypeVideo];
                    if ([tracks count] > 0) {
                        
                        AVAssetTrack *videoTrack = [tracks objectAtIndex:0];
                        [videoTrack loadValuesAsynchronouslyForKeys:@[@"preferredTransform"] completionHandler:^{
                            
                            if ([videoTrack statusOfValueForKey:@"preferredTransform" error:nil] == AVKeyValueStatusLoaded) {

                                dispatch_sync(dispatch_get_main_queue(), ^{
                                    [m_pPlayer replaceCurrentItemWithPlayerItem:item];
                                    if(m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_STOPPED || m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_PLAYING)
                                    {
                                        [[m_pPlayer currentItem] addOutput:m_pVideoOutput];
                                        [m_pVideoOutput requestNotificationOfMediaDataChangeWithAdvanceInterval:ONE_FRAME_DURATION];
                                        m_pCurrentVideoAssetReaderState->SetCurrentPlayerState(PLAYER_STATE_PLAYING);
                                        [m_pPlayer play];
                                        printf("Player State Changed to Playing");
                                    }
                                });
                                
                            }
                            
                        }];
                    }
                }
                
                else if ([asset statusOfValueForKey:@"tracks" error:&error] == AVKeyValueStatusFailed)
                {
                    NSLog(@"failed");
                }
                else if ([asset statusOfValueForKey:@"tracks" error:&error] == AVKeyValueStatusUnknown)
                {
                    NSLog(@"AVKeyValueStatusUnknown");
                }
            }];

        }
        
        void VideoAssetReaderService::RenderVideoBillBoard()
        {
            
            if(m_pVideoOutput)
            {
                if(m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() != PLAYER_STATE_PAUSED_BY_USER && m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() != PLAYER_STATE_PAUSED_BY_USER_IN_BUFFERING && m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() != PLAYER_STATE_STOPPED)
                    AvailableDuration();
                
                CMTime outputItemTime = kCMTimeInvalid;
                
                outputItemTime = [m_pVideoOutput itemTimeForHostTime:CACurrentMediaTime()];
                
                CVPixelBufferRef pixelBuffer = NULL;
                pixelBuffer = [m_pVideoOutput copyPixelBufferForItemTime:outputItemTime itemTimeForDisplay:NULL];
                m_renderedVideoTexture = NULL;
                
                if(pixelBuffer)
                {
                    CMSampleBufferRef m_resizedSampleBuffer = nullptr;
                    
                    GPUImageCreateResizedSampleBuffer(pixelBuffer, CGSizeMake(512, 256), &m_resizedSampleBuffer);
                    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(m_resizedSampleBuffer);
                    
                    CVOpenGLESTextureRef m_lumaTexture = NULL;
                    
                    if(imageBuffer)
                    {
                        CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault,
                                                                     m_videoTextureCache,
                                                                     imageBuffer,
                                                                     NULL,
                                                                     GL_TEXTURE_2D,
                                                                     GL_RGBA,
                                                                     512,
                                                                     256,
                                                                     GL_BGRA_EXT,
                                                                     GL_UNSIGNED_BYTE,
                                                                     0,
                                                                     &m_lumaTexture);
                    }
                    m_renderedVideoTexture = CVOpenGLESTextureGetName(m_lumaTexture);
                    
                    CFRelease(m_lumaTexture);
                    m_lumaTexture = nil;
                    
                    if (pixelBuffer != NULL) {
                        CFRelease(pixelBuffer);
                        pixelBuffer = NULL;
                    }
                    
                    if(m_resizedSampleBuffer)
                    {
                        CFRelease(m_resizedSampleBuffer);
                        m_resizedSampleBuffer = nil;
                    }
                    
                }
            }
            
//            if(m_renderedVideoTexture)
//                m_hasStartedPlaying = true;
            
            glBindTexture(GL_TEXTURE_2D, m_renderedVideoTexture);
        }
        
        void VideoAssetReaderService::AvailableDuration()
        {
            NSArray *loadedTimeRanges = [[m_pPlayer currentItem] loadedTimeRanges];
            if([loadedTimeRanges count] > 0)
            {
                CMTimeRange timeRange = [[loadedTimeRanges objectAtIndex:0] CMTimeRangeValue];
                Float64 startSeconds = CMTimeGetSeconds(timeRange.start);
                Float64 durationSeconds = CMTimeGetSeconds(timeRange.duration);
                NSTimeInterval result = startSeconds + durationSeconds;
                NSLog(@"Current Duration: %f",result);
                int duration = CMTimeGetSeconds(m_pPlayer.currentItem.duration);
                if(((result - m_lastPausedTime) > 4 || (int)result == duration) && (m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_PLAYING))
                {
                    m_lastPausedTime = (int)result;
                    printf("Player started playing after every four seconds");
                    [m_pPlayer play];
                }
                
                if(m_pPlayer.rate == 0.0 && (result - m_lastPausedTime) > 4 &&  m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_PAUSED_FOR_BUFFERING)
                {
                    m_lastPausedTime = (int)result;
                    m_pCurrentVideoAssetReaderState->SetCurrentPlayerState(PLAYER_STATE_PLAYING);
                    printf("Player started playing after buffering");
                    [m_pPlayer play];
                }
            
                if((m_pPlayer.rate == 0.0 && m_pCurrentVideoAssetReaderState->GetCurrentPlayerState() == PLAYER_STATE_PLAYING))
                {
                    m_lastPausedTime = (int)result;
                    m_pCurrentVideoAssetReaderState->SetCurrentPlayerState(PLAYER_STATE_PAUSED_FOR_BUFFERING);
                    printf("Player State Changed to Player state paused for buffering");
                    [m_pPlayer pause];
                }
            }
        }
        
        bool VideoAssetReaderService::IsVideoEnded() {
            
            return m_pPlayerObserver.isVideoEnded;
        }
        
    }
}
