// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewController.h"
#include "AppLocationDelegate.h"
#include "MathFunc.h"

using namespace Eegeo::iOS;

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    [[NSNotificationCenter defaultCenter] addObserver: self
     selector: @selector(onPause)
     name: @"handlePause"
     object: nil];

    [[NSNotificationCenter defaultCenter] addObserver: self
     selector: @selector(onResume)
     name: @"handleResume"
     object: nil];

    if([self respondsToSelector:@selector(setNeedsStatusBarAppearanceUpdate)])
    {
        [self setNeedsStatusBarAppearanceUpdate];
    }

    m_previousTimestamp = CFAbsoluteTimeGetCurrent();
    self.preferredFramesPerSecond = 30;
    m_pAppRunner = NULL;
}

- (void)onPause
{
    m_pAppRunner->Pause();

    GLKView* glkView = (GLKView *)self.view;
    glkView.context = nil;
}

- (void)onResume
{
    GLKView* glkView = (GLKView *)self.view;
    glkView.context = [EAGLContext currentContext];

    m_pAppRunner->Resume();
}

-(UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

- (void)viewWillLayoutSubviews
{
    if(m_pAppRunner == NULL)
    {
        m_pAppRunner = new AppRunner(*self, [self view]);
    }

    m_pAppRunner->NotifyViewLayoutChanged();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if(m_pAppRunner == NULL)
    {
        return;
    }

    CFTimeInterval timeNow = CFAbsoluteTimeGetCurrent();
    CFTimeInterval frameDuration = timeNow - m_previousTimestamp;
    
    const CFTimeInterval maxFrameInterval = 1.0f/self.preferredFramesPerSecond;
    
    frameDuration = Eegeo::Clamp<CFTimeInterval>(frameDuration, 0.0f, maxFrameInterval);
    
    m_pAppRunner->Update(static_cast<float>(frameDuration));

    const GLenum discards[]  = {GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT};
    Eegeo_GL(glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, discards));

    m_previousTimestamp = timeNow;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer
    shouldReceiveTouch:(UITouch *)touch
{
    for (UIView *subview in [self view].subviews)
    {
        if ([subview respondsToSelector: @selector(consumesTouch:)])
        {
            if([subview consumesTouch: touch])
            {
                return NO;
            }
        }

    }
    return YES;
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

-(void)willRotateToInterfaceOrientation: (UIInterfaceOrientation)orientation duration:(NSTimeInterval)duration
{

}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (m_pAppRunner == NULL) ? true : m_pAppRunner->ShouldAutoRotateToInterfaceOrientation(interfaceOrientation);
}

- (BOOL)shouldAutorotate
{
    UIInterfaceOrientation interfaceOrientation = [[UIApplication sharedApplication] statusBarOrientation];

    return (m_pAppRunner == NULL) ? true : m_pAppRunner->ShouldAutoRotateToInterfaceOrientation(interfaceOrientation);
}



@end