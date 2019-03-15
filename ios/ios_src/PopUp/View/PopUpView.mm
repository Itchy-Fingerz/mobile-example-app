// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PopUpView.h"
#include "ImageHelpers.h"
#include "PopUpViewInterop.h"
#include "UIHelpers.h"
#include "ViewController.h"

@implementation PopUpView

- (id) initView:(float) pixelScale
{
    self = [super init];

    if(self)
    {
        m_isOpen = false;
        m_pixelScale = pixelScale;
        self.backgroundColor = UIColor.clearColor;
        
        m_pInterop = Eegeo_NEW(ExampleApp::PopUp::View::PopUpViewInterop)(self);
        self.alpha = 0.f;
        self.pYouAreHereImage = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"you_are_here")] autorelease];
        [self addSubview:self.pYouAreHereImage];
        float imageHeight = self.pYouAreHereImage.image.size.height;
        float imgaeWidth = self.pYouAreHereImage.image.size.width;
        [self.pYouAreHereImage setFrame:CGRectMake(0, 0, imgaeWidth, imageHeight)];
    }

    return self;
}

- (void)dealloc
{
    [self.pYouAreHereImage removeFromSuperview];
    [self.pYouAreHereImage release];

    [self removeFromSuperview];
    [super dealloc];
    
    Eegeo_DELETE m_pInterop;
    
}

- (ExampleApp::PopUp::View::PopUpViewInterop*)getInterop
{
    return m_pInterop;
}

- (void)setPosition:(double)x ndY:(double)y {
    
    float imageHeight = self.pYouAreHereImage.image.size.height;
    float imgaeWidth = self.pYouAreHereImage.image.size.width;
    float popUpOffsetWithMarker = 20;
    self.frame = CGRectMake((x/m_pixelScale) - (imgaeWidth/2), (y/m_pixelScale) - (imageHeight+popUpOffsetWithMarker), imgaeWidth, imageHeight);

}

- (void) setFullyActive
{
    m_isOpen = true;
    if(self.alpha == 1.f)
    {
        return;
    }

    [self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
    if(self.alpha == 0.f)
    {
        return;
    }

    [self animateToAlpha:0.f];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    if(m_isOpen)
    {
        m_isOpen = false;
        [self setFullyInactive];
    }
    return false;
}

- (void) animateToAlpha:(float)alpha
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
     animations:^
    {
        self.alpha = alpha;
    }
     completion:^(BOOL finished) {

     }];
}


@end
