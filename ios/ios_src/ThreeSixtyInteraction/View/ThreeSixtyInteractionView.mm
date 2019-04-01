//
//  EegeoSearchResultPoiWeb.m
//  ExampleApp
//
//  Created by Sohail Khan on 1/14/19.
//

#import "ThreeSixtyInteractionView.h"
#include "EegeoJsonParser.h"
#import "UIButton+DefaultStates.h"
#include "ThreeSixtyInteractionViewInterop.h"


@interface ThreeSixtyInteractionView()<UIGestureRecognizerDelegate, UIWebViewDelegate>
{
}
@end

@implementation ThreeSixtyInteractionView

#pragma mark Init

- (void) layoutSubviews
{
    [super layoutSubviews];
}

-(void) performDynamicContentLayout
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    self.frame = CGRectMake(0,
                            0,
                            boundsWidth,
                            boundsHeight);
    
}
+ (id)initView
{
    ThreeSixtyInteractionView *containerView = [[[NSBundle mainBundle] loadNibNamed:@"ThreeSixtyInteractionView" owner:self options:nil] lastObject];
    if (containerView)
    {
        containerView.alpha = 0.f;
        containerView->m_pInterop = Eegeo_NEW(ExampleApp::ThreeSixtyInteraction::View::ThreeSixtyInteractionViewInterop)(containerView);
        containerView->m_stateChangeAnimationTimeSeconds = 0.2f;
        containerView->m_pController = [UIViewController alloc];
        [containerView->m_pController setView:containerView];
        [containerView.m_pSpinner startAnimating];
    }

    return containerView;
}

#pragma mark IBAction

- (IBAction)closeButtonPressed:(id)sender
{
    if(m_pWebView)
    {
        [m_pWebView stopLoading];
        [m_pWebView removeFromSuperview];
        [m_pWebView release];
    }
    m_pInterop->HandleCloseButtonTapped();
}

#pragma mark Dealloc

- (void)dealloc
{
    [m_pController release];
    [_m_pCloseButton release];
    [_m_pSpinner release];
    [m_pInterop release];
    [super dealloc];
}

#pragma mark Search Poi view delage
- (void) setContent:(std::string)url
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    
    m_pWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, boundsWidth, boundsHeight)];
    [m_pWebView setBackgroundColor:[UIColor clearColor]];
    m_pWebView.delegate = self;
    
    NSString *urlString = [NSString stringWithCString:url.c_str() encoding:[NSString defaultCStringEncoding]];
    [m_pWebView setHidden:true];
    [self.m_pSpinner startAnimating];
    [[UIApplication sharedApplication] setStatusBarHidden:YES];
    [self.m_pCloseButton setHidden:YES];
    [m_pWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlString]]];
    [self performDynamicContentLayout];

    [self addSubview:m_pWebView];
    [self bringSubviewToFront:self.m_pCloseButton];
    [self bringSubviewToFront:self.m_pSpinner];
}


- (void) setFullyActive
{
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
    [[UIApplication sharedApplication] setStatusBarHidden:false];
    [self animateToAlpha:0.f];
}

#pragma mark class methods

- (void) setActiveStateToIntermediateValue:(float)openState
{
    self.alpha = openState;
}
- (ExampleApp::ThreeSixtyInteraction::View::ThreeSixtyInteractionViewInterop*) getInterop
{
    return m_pInterop;
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

#pragma mark uiwebview delegate

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return YES;
}
- (void)webViewDidStartLoad:(UIWebView *)webView
{
    webView.scrollView.scrollEnabled = false;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    [webView setHidden:false];
    [self.m_pCloseButton setHidden:NO];
    webView.scrollView.scrollEnabled = true;
    [self.m_pSpinner stopAnimating];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    [self.m_pCloseButton setHidden:NO];
    [m_pWebView setHidden:false];
    NSString* path = [[NSBundle mainBundle] pathForResource:@"page_not_found" ofType:@"html"];
    NSString* html = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:NULL];
    [webView loadHTMLString:html baseURL:nil];
}

@end
