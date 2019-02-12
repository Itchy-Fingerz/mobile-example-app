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
        
        self.pViewforCamera = [[[UIView alloc] init] autorelease];
        self.pViewforCamera.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentView addSubview:self.pViewforCamera];
        
    }

    return self;
}

- (void)dealloc
{
    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
    
    [self.pViewforCamera removeFromSuperview];
    [self.pViewforCamera release];

    [self.pOverlay release];

    [self.pContentView removeFromSuperview];
    [self.pContentView release];
    
    [self.pCaptureSession release];
    [self.pVideoPreviewLayer release];
    [self.pOverlay release];
    
    
    [self removeFromSuperview];
    [super dealloc];
    
    Eegeo_DELETE m_pInterop;
    
}

- (void)layoutSubviews
{
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
    self.pViewforCamera.frame = CGRectMake(marginCameraView, marginCameraView,self.frame.size.width-(2*marginCameraView),(self.frame.size.height - contentY)-(2*marginCameraView));
    
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
    [self stopReading];
    _pIsReading = NO;
    m_pInterop->CloseTapped();
}

#pragma mark - Private Methods And QR Scanning

- (void)addOverlay
{
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, self.pViewforCamera.frame.size.width, self.pViewforCamera.frame.size.height)];
    [imageView setImage:[UIImage imageNamed:@"scan_outline.png"]];
    [self.pViewforCamera.layer insertSublayer:imageView.layer above:_pVideoPreviewLayer];
}

- (void)startScan {
    
    if (!_pIsReading)
    {
        if ([self startReading])
        {
            NSLog(@"Scanning for QR Code...");
        }else
        {
            NSLog(@"FailedScanning for QR Code...");
        }
    }
    else
    {
        [self stopReading];
    }
    _pIsReading = !_pIsReading;
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
    
    _pCaptureSession = [[AVCaptureSession alloc] init];
    
    [_pCaptureSession addInput:input];
    
    AVCaptureMetadataOutput *captureMetadataOutput = [[AVCaptureMetadataOutput alloc] init];
    
    [_pCaptureSession addOutput:captureMetadataOutput];
    
    dispatch_queue_t dispatchQueue;
    
    dispatchQueue = dispatch_queue_create("myQueue", NULL);
    
    [captureMetadataOutput setMetadataObjectsDelegate:self queue:dispatchQueue];
    
    [captureMetadataOutput setMetadataObjectTypes:[NSArray arrayWithObject:AVMetadataObjectTypeQRCode]];
    
    
    _pVideoPreviewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:_pCaptureSession];
    
    [_pVideoPreviewLayer setVideoGravity:AVLayerVideoGravityResizeAspectFill];
    
    [_pVideoPreviewLayer setFrame:_pViewforCamera.layer.bounds];
    
    [_pViewforCamera.layer addSublayer:_pVideoPreviewLayer];
    
    [_pCaptureSession startRunning];
    
    [self addOverlay];
    
    return YES;
    
}


-(void)stopReading{
    [_pCaptureSession stopRunning];
    _pCaptureSession = nil;
    [_pVideoPreviewLayer removeFromSuperlayer];
}

-(void)playBeepSound
{
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);//http://iphonedevwiki.net/index.php/AudioServices
}

-(void)captureOutput:(AVCaptureOutput *)captureOutput didOutputMetadataObjects:(NSArray *)metadataObjects fromConnection:(AVCaptureConnection *)connection
{
    if (metadataObjects != nil && [metadataObjects count] > 0) {
        
        AVMetadataMachineReadableCodeObject *metadataObj = [metadataObjects objectAtIndex:0];
        
        if ([[metadataObj type] isEqualToString:AVMetadataObjectTypeQRCode])
        {
            
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
            
        }
        
    }
}

-(void)onQRScanCompleted:(NSString *)resultScanned
{
    if (resultScanned != nil && _pIsReading)
    {
        [self stopReading];
        _pIsReading = NO;
        NSLog(@"QR Scanned %@",resultScanned);
        NSURL *url  = [[NSURL alloc] initWithString:resultScanned];
        NSArray *params = [url pathComponents];
        NSLog(@"QR Scanned*********params: %@",params);
        //TODO Need to parse actual scheme deep link data once it is confirmed
        if (params.count == 6) // Currently assuming we will have 6 total path components
        {
            NSString *locationMode = params[1];
            double lat = [params[2] doubleValue];
            double lon = [params[3] doubleValue];
            NSString *indoorId = params[4];
            NSInteger orientation = [params[5] integerValue];
            m_pInterop->OnQRScanCompleted([locationMode UTF8String],lat,lon,[indoorId UTF8String],orientation);
        }
        else
        {
            //Temporary else condition for testing purpose
            m_pInterop->OnQRScanCompleted("indoor",31.496739,74.421984,"EIM-908710f5-3ed3-408d-a92b-c7749d9f1ae1",0);
        }
        m_pInterop->CloseTapped();
    }
    else if (resultScanned == nil)
    {
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
