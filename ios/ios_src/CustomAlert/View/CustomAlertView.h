// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#import <UIKit/UIKit.h>
#include "CustomAlertViewIncludes.h"


@class CustomAlertView;

@interface CustomAlertView : UIView
{
    ExampleApp::CustomAlert::View::CustomAlertViewInterop* m_pInterop;
    UIViewController* m_pController;
    
    float m_screenWidth;
    float m_screenHeight;
}

- (id) initWithDimensions:(float)width
                         :(float)height
                         :(float)pixelScale;
+(CustomAlertView*)CustomAlertViewWithInterop;

- (ExampleApp::CustomAlert::View::CustomAlertViewInterop*) getInterop;

@end
