//
//  EegeoSearchResultPoiWeb.m
//  ExampleApp
//
//  Created by Sohail Khan on 1/14/19.
//

#import "EegeoSearchResultPoiWebView.h"
#include "EegeoJsonParser.h"
#import "UIButton+DefaultStates.h"

@interface EegeoSearchResultPoiWebView()<UIGestureRecognizerDelegate, UIWebViewDelegate>
{
}
@end

@implementation EegeoSearchResultPoiWebView

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
+ (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop
{
    EegeoSearchResultPoiWebView *containerView = [[[NSBundle mainBundle] loadNibNamed:@"EegeoSearchResultPoiWebView" owner:self options:nil] lastObject];
    if (containerView)
    {
        containerView.alpha = 0.f;
        containerView->m_pInterop = pInterop;
        containerView->m_stateChangeAnimationTimeSeconds = 0.2f;
        containerView->m_pController = [UIViewController alloc];
        [containerView->m_pController setView:containerView];
        [containerView.m_pSpinner startAnimating];
        containerView.m_pWebView.delegate = containerView;
        containerView.m_pWebView.backgroundColor = [UIColor clearColor];
        containerView.backgroundColor = [UIColor clearColor];
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }

    return containerView;
}

#pragma mark IBAction

- (IBAction)closeButtonPressed:(id)sender
{
    m_pInterop->HandleCloseClicked();
}

#pragma mark Dealloc

- (void)dealloc
{
    [[UIApplication sharedApplication] setStatusBarHidden:NO];
    [m_pController release];
    [_m_pCloseButton release];
    [_m_pWebView release];
    [_m_pSpinner release];
    [super dealloc];
}

#pragma mark Search Poi view delage

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    m_eegeoModel = ExampleApp::Search::EegeoPois::SdkModel::TransformToEegeoSearchResult(m_model);
    
    if(!m_eegeoModel.GetCustomViewUrl().empty())
    {
        NSString *url = [NSString stringWithCString:m_eegeoModel.GetCustomViewUrl().c_str()
                                           encoding:[NSString defaultCStringEncoding]];
        
        [self.m_pWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:url]]];
        [self performDynamicContentLayout];
    }
    
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

#pragma mark class methods

- (void) setActiveStateToIntermediateValue:(float)openState
{
    self.alpha = openState;
}

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)getInterop
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
    webView.scrollView.scrollEnabled = true;
    [self.m_pSpinner stopAnimating];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    NSString* path = [[NSBundle mainBundle] pathForResource:@"page_not_found" ofType:@"html"];
    NSString* html = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:NULL];
    [webView loadHTMLString:html baseURL:nil];
}

@end
