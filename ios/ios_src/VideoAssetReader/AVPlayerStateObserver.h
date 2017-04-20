
#import <Foundation/Foundation.h>
#include <AVFoundation/AVFoundation.h>


@interface AVPlayerStateObserver : NSObject <AVPlayerItemOutputPullDelegate> {
    
    AVPlayer *m_pPlayer;
    BOOL m_isVideoEnded;
}

-(id)initWithPlayer:(AVPlayer *)player;
-(BOOL)isVideoEnded;
@end