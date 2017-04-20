// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AVPlayerStateObserver.h"

#import <Foundation/Foundation.h>

void *kCurrentItemDidChangeKVO  = &kCurrentItemDidChangeKVO;

@implementation AVPlayerStateObserver

-(id)initWithPlayer:(AVPlayer *)player
{
    if(self = [super init])
    {
        m_pPlayer = player;
        
        [[NSNotificationCenter defaultCenter]
         addObserver:self
         selector:@selector(TrackDidEndNotification:)
         name:AVPlayerItemDidPlayToEndTimeNotification
         object:player.currentItem];
        m_isVideoEnded = false;
        
    }
    
    return self;
}

-(void)TrackDidEndNotification:(NSNotification*)notification
{
    m_isVideoEnded = true;
}

#pragma mark - AVPlayerItemOutputPullDelegate


- (void)outputMediaDataWillChange:(AVPlayerItemOutput *)sender
{
    [m_pPlayer play];
}

-(BOOL)isVideoEnded
{
    return m_isVideoEnded;
}

@end
