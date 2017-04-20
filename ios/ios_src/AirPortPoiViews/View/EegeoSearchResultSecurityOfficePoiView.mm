// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#import "EegeoSearchResultSecurityOfficePoiView.h"

@interface EegeoSearchResultSecurityOfficePoiView()
{
    IBOutletCollection(UIButton) NSArray *m_pRatingButtons;
}
@end

@implementation EegeoSearchResultSecurityOfficePoiView

- (IBAction)RatingButtonPressed:(id)sender
{
    
    UIButton *selectedButton = (UIButton *)sender;
    NSInteger selectButtonNumber = selectedButton.tag;
    
    for(UIButton *button in m_pRatingButtons)
    {
        if(button.tag <= selectButtonNumber)
        {
            [button setBackgroundImage:[UIImage imageNamed:@"poi_security_office_rating_selected.png"] forState:UIControlStateNormal];
        }
        else
        {
            [button setBackgroundImage:[UIImage imageNamed:@"poi_security_office_rating_unselected.png"] forState:UIControlStateNormal];

        }
    }
}


- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
}

- (void) setFullyActive
{
    [m_pController setView:self];
    if(self.alpha == 1.f)
    {
        return;
    }
    
    [self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
    [m_pController setView:nil];
    if(self.alpha == 0.f)
    {
        return;
    }
    
    [self animateToAlpha:0.f];
}

- (void) animateToAlpha:(float)alpha
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.alpha = alpha;
     }];
}

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)getInterop
{
    return NULL;
}

+(EegeoSearchResultSecurityOfficePoiView *)EegeoSearchResultSecurityOfficePoiViewWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop
{
    EegeoSearchResultSecurityOfficePoiView *poiView = (EegeoSearchResultSecurityOfficePoiView*)[[[NSBundle mainBundle] loadNibNamed:@"SecurityOfficePoiView" owner:self options:nil] objectAtIndex:0];
    poiView->m_pInterop = pInterop;
    
    poiView->m_pController = [UIViewController alloc];
    [poiView->m_pController setView:poiView];
    poiView->m_stateChangeAnimationTimeSeconds = 0.2f;
    poiView.alpha = 0.f;
    
    return poiView;
}

- (void) layoutSubviews
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    
    float boundsOccupyMultiplierHeight;
    
    UIInterfaceOrientation currentOrientation = [UIApplication sharedApplication].statusBarOrientation;
    
    if(currentOrientation == UIInterfaceOrientationLandscapeLeft || currentOrientation == UIInterfaceOrientationLandscapeRight)
    {
        boundsOccupyMultiplierHeight = 0.755f;
    }
    else
    {
        boundsOccupyMultiplierHeight = 0.9f;
    }
    const float boundsOccupyMultiplierWidth = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth*boundsOccupyMultiplierWidth, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplierHeight;
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    
    float mainWindowY;
    
    if(currentOrientation == UIInterfaceOrientationLandscapeLeft || currentOrientation == UIInterfaceOrientationLandscapeRight)
    {
        mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.489f);
    }
    else
    {
        mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    }
    
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
}

-(IBAction)HandleClosedButtonSelected:(id) sender
{
    m_pInterop->HandleCloseClicked();
}

-(void)dealloc
{
    [m_pController release];
    [m_pRatingButtons release];
    [super dealloc];
}



@end
