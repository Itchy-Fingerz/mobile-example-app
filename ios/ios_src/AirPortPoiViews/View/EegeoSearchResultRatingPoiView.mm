// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "EegeoSearchResultRatingPoiView.h"

@interface EegeoSearchResultRatingPoiView()<UITextViewDelegate,UIScrollViewDelegate>
{

    IBOutlet UILabel *m_pSubTitle;
    IBOutlet UILabel *m_pTitleLabel;
    IBOutletCollection(UIButton) NSArray *m_pRatingButtonCollection;
    IBOutlet UITextView *m_pReviewTextField;
    IBOutlet UIScrollView *m_pScrollView;
    IBOutlet UIView *m_pReviewView;
    IBOutlet NSLayoutConstraint *m_pCouponViewHeightConstraint;
    IBOutlet NSLayoutConstraint *m_pContentViewHeightConstraint;
    IBOutlet UIImageView *m_pCoverImage;
    IBOutlet UIImageView *m_pPoiLogoImageView;
    IBOutlet UIImageView *m_pDiscountLogoImageView;
    IBOutlet UILabel *m_pDiscountDescriptionLabel;
    IBOutlet UILabel *m_pWebsiteLabel;
    
    IBOutlet UIButton *m_pscrollDownButton;
}
@end
@implementation EegeoSearchResultRatingPoiView

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    m_pTitleLabel.text = [NSString stringWithCString:pModel->GetTitle().c_str()
                                            encoding:[NSString defaultCStringEncoding]];
    
    if ([m_pTitleLabel.text isEqualToString:@"Duty Free Shopping"] || [m_pTitleLabel.text isEqualToString:@"Hogo Boss"] || [m_pTitleLabel.text isEqualToString:@"Armani"]  )
    {
        m_pContentViewHeightConstraint.constant -= m_pCouponViewHeightConstraint.constant;
        m_pCouponViewHeightConstraint.constant = -1;
        
    }
    else if([m_pTitleLabel.text isEqualToString:@"McDonalds"])
    {
        m_pCoverImage.image = [UIImage imageNamed:@"McDonaldsImg02"];
        m_pPoiLogoImageView.image = [UIImage imageNamed:@"McDonald-icon"];
        m_pDiscountLogoImageView.image = [UIImage imageNamed:@"20Discount"];
        m_pSubTitle.text = @"McDonalds Chicken Sandwich - always a crowd pleaser for hungry geezers         …more";
        m_pDiscountDescriptionLabel.text = @"Chicken Legend, Big Tasty, Big Flavour wraps, Vegetarian, Drinks & Shakes, Desserts & Treats ";
        m_pWebsiteLabel.hidden = false;
        
    }
    
    rapidjson::Document json;
    std::string descriptionJsonString = "";
    if (!json.Parse<0>(pModel->GetJsonData().c_str()).HasParseError() && json.HasMember("subTitleDescription"))
    {
        std::string description = json["subTitleDescription"].GetString();
        m_pSubTitle.text = [NSString stringWithCString:description.c_str()
                                              encoding:[NSString defaultCStringEncoding]];
    }
    else if (pModel->GetSubtitle() != "")
    {
        m_pSubTitle.text = [NSString stringWithCString:pModel->GetSubtitle().c_str()
                                              encoding:[NSString defaultCStringEncoding]];
    }


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

- (BOOL)consumesTouch:(UITouch *)touch
{
    return self.alpha > 0.f;
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
    return m_pInterop;
}

+(EegeoSearchResultRatingPoiView *)EegeoSearchResultRatingPoiViewWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop
{
    
    EegeoSearchResultRatingPoiView *poiView = (EegeoSearchResultRatingPoiView*)[[[NSBundle mainBundle] loadNibNamed:@"CouponPoiView" owner:self options:nil] objectAtIndex:0];
    poiView->m_pInterop = pInterop;
    
    poiView->m_pController = [UIViewController alloc];
    [poiView->m_pController setView:poiView];
    poiView->m_stateChangeAnimationTimeSeconds = 0.2f;
    poiView.alpha = 0.f;
    [poiView->m_pReviewTextField setDelegate:poiView];
    poiView->m_pReviewView.layer.cornerRadius = 5;
    poiView->m_pScrollView.delegate = poiView;
    //poiView->m_pReviewTextField.text = @"";
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
- (IBAction)ScrollDownButtonPressed:(id)sender
{
    CGPoint bottomOffset = CGPointMake(0, m_pScrollView.contentSize.height - m_pScrollView.bounds.size.height);
    [m_pScrollView setContentOffset:bottomOffset animated:YES];
    m_pscrollDownButton.hidden = true;
}


- (IBAction)RatingButtonPressed:(id)sender
{

    UIButton *selectedButton = (UIButton *)sender;
    NSInteger selectButtonNumber = selectedButton.tag;
    
    for(UIButton *button in m_pRatingButtonCollection)
    {
        if(button.tag <= selectButtonNumber)
        {
            [button setSelected:true];
        }
        else
        {
            [button setSelected:false];
        }
    }

}

-(IBAction)HandleClosedButtonSelected:(id) sender
{
    m_pInterop->HandleCloseClicked();
    
}

-(void)dealloc
{
    [m_pRatingButtonCollection release];
    [m_pController release];
    [m_pTitleLabel release];
    [m_pSubTitle release];
    [m_pReviewTextField release];
    [m_pScrollView release];
    [m_pReviewView release];
    [m_pCouponViewHeightConstraint release];
    [m_pContentViewHeightConstraint release];
    [m_pCoverImage release];
    [m_pPoiLogoImageView release];
    [m_pDiscountLogoImageView release];
    [m_pDiscountDescriptionLabel release];
    [m_pWebsiteLabel release];
    [m_pscrollDownButton release];
    [super dealloc];
}

#pragma mark uiscrollview delegate

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView
{
    if (scrollView.contentOffset.y < 10)
    {
        m_pscrollDownButton.hidden = false;
    }
    else if (scrollView.contentOffset.y > (m_pScrollView.contentSize.height - m_pScrollView.bounds.size.height)- 100)
    {
        m_pscrollDownButton.hidden = true;
    }
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{

}

#pragma mark uitextview delegate

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView
{
    int move_up = 50;
    if ( UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad )
    {
         move_up = 200;
    }
    [m_pScrollView setContentOffset:CGPointMake(m_pScrollView.contentOffset.x, m_pScrollView.contentOffset.y + move_up) animated:true];
    
    // Look for the default message and highlight it if present
    NSRange defaultMsgRange = [m_pReviewTextField.text rangeOfString:@"Enter Text Review..." options:NSAnchoredSearch];
    
    BOOL isDefaultMsg = !(defaultMsgRange.location == NSNotFound && defaultMsgRange.length == 0);
    if (isDefaultMsg)
    {
        [m_pReviewTextField setText:@""];
    }
    
    return true;
}

- (BOOL)textViewShouldEndEditing:(UITextView *)textView
{
    int move_down = 50;
    if ( UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad )
    {
        move_down = 200;
    }
    [m_pScrollView setContentOffset:CGPointMake(m_pScrollView.contentOffset.x, m_pScrollView.contentOffset.y - move_down) animated:true];
    


    return true;
}

-(BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    if([text isEqualToString:@"\n"])
    {
        [textView resignFirstResponder];

    }
    return true;
}



@end
