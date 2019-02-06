// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "QRScanViewInterop.h"
#include "UIHelpers.h"
#include "ViewController.h"
#import "UIButton+DefaultStates.h"

@implementation QRScanView

- (id)initView
{
    self = [super init];

    if(self)
    {
        m_pInterop = Eegeo_NEW(ExampleApp::QRScan::View::QRScanViewInterop)(self);
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;

        self.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        
        self.pHeaderView = [[[HeaderView alloc] initWithWidth:200 title:@"Scan My Location"] autorelease];
        [self addSubview:self.pHeaderView];
        
        [self.pHeaderView addTarget:self action:@selector(onCloseButtonTapped) forControlEvents:UIControlEventTouchUpInside];
        
        self.pContentView = [[[UIView alloc] init] autorelease];
        self.pContentView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview:self.pContentView];
        
        self.viewforCamera = [[[UIView alloc] init] autorelease];
        self.viewforCamera.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentView addSubview:self.viewforCamera];
        
    }

    return self;
}

- (void)dealloc
{
    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
    
    [self.viewforCamera removeFromSuperview];
    [self.viewforCamera release];

    [self.overlay release];

    [self.pContentView removeFromSuperview];
    [self.pContentView release];
    
    [self removeFromSuperview];
    [super dealloc];
    
    Eegeo_DELETE m_pInterop;
    
}

- (void)layoutSubviews
{
//    UIViewController *viewController = [UIApplication sharedApplication].delegate.window.rootViewController;
//    self.frame = [viewController largePopoverFrame];
//
    CGFloat rowHeight = 250;
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const float boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
    const float mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin);
    
    CGFloat contentY = self.pHeaderView.frame.origin.y +  self.pHeaderView.frame.size.height + 10;

    const CGFloat contentHeight = rowHeight + innerMargin.top + innerMargin.bottom ;
    const float mainWindowHeight = self.pHeaderView.frame.size.height + contentHeight;
    
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    self.pHeaderView.width = self.frame.size.width;
    [self.pHeaderView layoutIfNeeded];
    
    
    self.pContentView.frame = CGRectMake(0.0,
                                               contentY,
                                               self.frame.size.width,
                                               self.frame.size.height - contentY);
    
    CGFloat marginCameraView = 5.0;
    self.viewforCamera.frame = CGRectMake(marginCameraView, marginCameraView,self.frame.size.width-(2*marginCameraView),(self.frame.size.height - contentY)-(2*marginCameraView));
    
}

- (ExampleApp::QRScan::View::QRScanViewInterop*)getInterop
{
    return m_pInterop;
}

- (void) setFullyActive
{
    if(self.alpha == 1.f)
    {
        return;
    }

    [self animateToAlpha:1.f];

    // Start QR Code scanning when active
    [self startScan];

}

- (void) setFullyInactive
{
    if(self.alpha == 0.f)
    {
        return;
    }

    [self animateToAlpha:0.f];
}

- (void) setActiveStateToIntermediateValue:(float)openState
{
    self.alpha = openState;
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
    }
     completion:^(BOOL finished) {
         
     }];
}

- (void)onCloseButtonTapped
{
    //wrld://fixedlocation/indoor/31.496739/74.421984/EIM-908710f5-3ed3-408d-a92b-c7749d9f1ae1/0
    [self stopReading];
    _isReading = NO;
    m_pInterop->CloseTapped();
//    m_pInterop->OnQRScanCompleted("fixedlocation/indoor",31.496739,74.421984,"EIM-908710f5-3ed3-408d-a92b-c7749d9f1ae1",0);
}

#pragma mark - Private Methods And QR Scanning

- (void)addOverlay
{
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, self.viewforCamera.frame.size.width, self.viewforCamera.frame.size.height)];
    [imageView setImage:[UIImage imageNamed:@"scan_outline.png"]];
    [self.viewforCamera.layer insertSublayer:imageView.layer above:_videoPreviewLayer];
}

- (void)startScan {
    
    if (!_isReading)
    {
        if ([self startReading])
        {
            NSLog(@"Scanning for QR Code...");
        }else{
            NSLog(@"FailedScanning for QR Code...");
        }
    }
    else
    {
        [self stopReading];
    }
    _isReading = !_isReading;
}

-(BOOL)startReading{
    NSError *error;
    
    AVCaptureDevice *captureDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    
    if (captureDevice.position == AVCaptureDevicePositionBack) {
        NSLog(@"back camera");
    }else if (captureDevice.position == AVCaptureDevicePositionFront){
        NSLog(@"Front Camera");
    }else{
        NSLog(@"Unspecified");
    }
    
    AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:captureDevice error:&error];
    
    if (!input)
        
    {
        NSLog(@"%@", [error localizedDescription]);
        return NO;
    }
    
    _captureSession = [[AVCaptureSession alloc] init];
    
    [_captureSession addInput:input];
    
    AVCaptureMetadataOutput *captureMetadataOutput = [[AVCaptureMetadataOutput alloc] init];
    
    [_captureSession addOutput:captureMetadataOutput];
    
    dispatch_queue_t dispatchQueue;
    
    dispatchQueue = dispatch_queue_create("myQueue", NULL);
    
    [captureMetadataOutput setMetadataObjectsDelegate:self queue:dispatchQueue];
    
    [captureMetadataOutput setMetadataObjectTypes:[NSArray arrayWithObject:AVMetadataObjectTypeQRCode]];
    
    
    _videoPreviewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:_captureSession];
    
    [_videoPreviewLayer setVideoGravity:AVLayerVideoGravityResizeAspectFill];
    
    [_videoPreviewLayer setFrame:_viewforCamera.layer.bounds];
    
    [_viewforCamera.layer addSublayer:_videoPreviewLayer];
    
    [_captureSession startRunning];
    
    [self addOverlay];
    
    
    return YES;
    
}


-(void)stopReading{
    [_captureSession stopRunning];
    _captureSession = nil;
    [_videoPreviewLayer removeFromSuperlayer];
}

-(void)playBeepSound
{
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);//http://iphonedevwiki.net/index.php/AudioServices
}

-(void)captureOutput:(AVCaptureOutput *)captureOutput didOutputMetadataObjects:(NSArray *)metadataObjects fromConnection:(AVCaptureConnection *)connection
{
    if (metadataObjects != nil && [metadataObjects count] > 0) {
        
        AVMetadataMachineReadableCodeObject *metadataObj = [metadataObjects objectAtIndex:0];
        
        if ([[metadataObj type] isEqualToString:AVMetadataObjectTypeQRCode]) {
            
            [self playBeepSound];
            NSString * qrString = [metadataObj stringValue];
            
            if ([qrString containsString:@"fixedlocation"]) {
                NSLog(@"QR Scanned %@",qrString);
                [self performSelectorOnMainThread:@selector(onQRScanCompleted:) withObject:qrString waitUntilDone:NO];
            }
            else
                
            {
                //you can show your custom alert like - there is no HTTP link present in the QR Code. //
                NSLog(@"Not Valid QR Scanned %@",qrString);
                [self performSelectorOnMainThread:@selector(onQRScanCompleted:) withObject:nil waitUntilDone:NO];
            }
            
//            [self performSelectorOnMainThread:@selector(stopReading) withObject:nil waitUntilDone:NO];
            
        }
        
    }
}

-(void)onQRScanCompleted:(NSString *)resultScanned
{
    if (resultScanned != nil && _isReading)
    {
        [self stopReading];
        _isReading = NO;
        NSLog(@"QR Scanned %@",resultScanned);
        NSURL *url  = [[NSURL alloc] initWithString:resultScanned];
        NSString *host = [url host];
        NSArray *params = [url pathComponents];
        NSLog(@"QR Scanned*********params: %@,%@",host,params);
        m_pInterop->OnQRScanCompleted("fixedlocation/indoor",31.496739,74.421984,"EIM-908710f5-3ed3-408d-a92b-c7749d9f1ae1",0);

        m_pInterop->CloseTapped();
    }else{
        NSLog(@"QR Scanned*********Invalid:");
        [self notifyInvalidQRCode];
    }
}
- (void) notifyInvalidQRCode
{
    UIAlertController *alertController = ExampleApp::Helpers::UIHelpers::CreateSimpleAlert(@"Invalid QR Code",
                                                                                           @"Please scan a valid QR code.",
                                                                                           @"OK");
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    UIViewController *viewController = window.rootViewController;
    [viewController presentViewController:alertController animated:YES completion:nil];
}


@end
