// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomAlertView.h"
#include "CustomAlertViewInterop.h"
#include "UIHelpers.h"

@interface CustomAlertView()
{

    IBOutlet UILabel *m_pMessageLabel;
    IBOutlet UIButton *m_pAcceptButton;
    IBOutlet UIButton *m_pCancelButton;
}

@end
@implementation CustomAlertView


- (id) initWithDimensions:(float)width
                         :(float)height
                         :(float)pixelScale
{
    if(self = [super init])
    {
        
        
//        m_pController = [UIViewController alloc];
//        [m_pController setView:self];
//        
//        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
//        
        m_pInterop = new ExampleApp::CustomAlert::View::CustomAlertViewInterop(self);
        self.hidden = true;
//
//        m_width = 140 * m_pixelScale;
//        m_height = 52 * m_pixelScale;
//        
//        float xPosition = 0.0f;
//        if(ExampleApp::Helpers::UIHelpers::UsePhoneLayout())
//        {
//            m_yPosActive = (20 * m_pixelScale);
//            m_yPosInactive = (-m_height);
//            
//            xPosition = ((m_screenWidth * 0.5f) - (m_width * 0.5f));
//        }
//        else
//        {
//            m_yPosActive = m_screenHeight - m_height - (8 * m_pixelScale);
//            m_yPosInactive = (m_screenWidth + m_height);
//            
//            xPosition = ((m_screenWidth) - (m_width) - (8 * m_pixelScale));
//        }
//        
        self.frame = CGRectMake(0,
                                0,
                                m_screenWidth,
                                m_screenHeight);
        
        self.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0.2];
        
        
        
        UIView *customAlertView = [[[NSBundle mainBundle] loadNibNamed:@"CustomAlertView" owner:self options:nil] objectAtIndex:0];
        
        UIButton *yesBtn = (UIButton *)[customAlertView viewWithTag:998];
        [yesBtn addTarget:self action:@selector(AcceptButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        
        UIButton *noBtn = (UIButton *)[customAlertView viewWithTag:999];
        [noBtn addTarget:self action:@selector(CancelButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        
        self.hidden = true;

        float alertWidth = 0.0;
        if(ExampleApp::Helpers::UIHelpers::UsePhoneLayout())
        {
            alertWidth = m_screenWidth * 0.8;

        }
        else
        {
            alertWidth = m_screenWidth * 0.45;
        }

        float alertHeight = alertWidth * 0.4303797468;
        [customAlertView setFrame:CGRectMake(0, 0, alertWidth, alertHeight)];
        [customAlertView setCenter:CGPointMake(m_screenWidth/2, m_screenHeight/2)];
        customAlertView.layer.borderColor = [UIColor whiteColor].CGColor;
        customAlertView.layer.borderWidth = 2.0f;
        
        noBtn.layer.borderColor = [UIColor whiteColor].CGColor;
        noBtn.layer.borderWidth = 1.0f;
        [self addSubview:customAlertView];
        
//
//        self.pShadowGradient = [[UIView alloc] initWithFrame:CGRectMake(0, 0, m_screenWidth, m_height)];
//        
//        CAGradientLayer *gradient = [CAGradientLayer layer];
//        gradient.frame =  CGRectMake(0, 0.f, m_screenWidth, m_screenHeight - m_yPosActive);
//        
//        UIColor *topColor = [UIColor clearColor];
//        UIColor *bottomColor = [[UIColor blackColor] colorWithAlphaComponent:0.85];
//        
//        gradient.colors = [NSArray arrayWithObjects:(id)[topColor CGColor], (id)[bottomColor CGColor], nil];
//        
//        [self.pShadowGradient.layer insertSublayer:gradient atIndex:0];
//        self.pShadowGradient.layer.shouldRasterize = YES;
//        [self.pShadowGradient setAlpha:0.0];
//        [self addSubview:self.pShadowGradient];
//        
//        m_stateChangeAnimationTimeSeconds = 0.2f;
//        self.pButton = [[UIButton alloc] initWithFrame:CGRectMake(xPosition, 0, m_width, m_height)];
//        [self addSubview: self.pButton];
//        
//        [self.pButton addTarget:self action:@selector(onClick:) forControlEvents:UIControlEventTouchUpInside];
//        [self updateWatermarkData: watermarkData];
//        
//        [self.pButton setAlpha:0.8];
//        
//        m_alignAlongBottom = false;
//        
//        
//#ifdef AUTOMATED_SCREENSHOTS
//        // move offscreen
//        m_yPosActive = -10000.f;
//        m_yPosActive = -10000.f;
//#endif
//        
//        m_alignAlongBottom = false;
        
        
    
    }
    
    return self;
}

+(CustomAlertView*)CustomAlertViewWithInterop
{
    CustomAlertView *customAlertView = (CustomAlertView*)[[[NSBundle mainBundle] loadNibNamed:@"CustomAlertView" owner:self options:nil] objectAtIndex:0];
    customAlertView->m_pInterop = new ExampleApp::CustomAlert::View::CustomAlertViewInterop(customAlertView);
    customAlertView.hidden = true;
    
    return customAlertView;

}

- (ExampleApp::CustomAlert::View::CustomAlertViewInterop *)getInterop
{
    return m_pInterop;
}
- (IBAction)AcceptButtonPressed:(id)sender
{
    self.hidden = true;
    m_pInterop->OnAccepet();
}

- (IBAction)CancelButtonPressed:(id)sender
{
    self.hidden = true;
    m_pInterop->OnCancel();
}


- (void)dealloc
{
    [m_pMessageLabel release];
    [m_pAcceptButton release];
    [m_pCancelButton release];
    [super dealloc];
}
@end
