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
        
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;

        m_pInterop = new ExampleApp::CustomAlert::View::CustomAlertViewInterop(self);
        self.hidden = true;

        self.frame = CGRectMake(0,
                                0,
                                m_screenWidth,
                                m_screenHeight);
        
        self.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0.2];
        
        
        
        customAlertView = [[[NSBundle mainBundle] loadNibNamed:@"CustomAlertView" owner:self options:nil] objectAtIndex:0];
        
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
        
    }
    
    return self;
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

- (BOOL)consumesTouch:(UITouch *)touch
{
    if(!self.isHidden)
        return true;
    else
        return false;
}

- (void)dealloc
{
    [m_pMessageLabel release];
    [m_pAcceptButton release];
    [m_pCancelButton release];
    [super dealloc];
}
@end
