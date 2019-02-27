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

+(QRScanView*)loadQRScanViewWithBus:(ExampleApp::ExampleAppMessaging::TMessageBus&) messageBus
{
    NSArray* nibViews = [[NSBundle mainBundle] loadNibNamed:@"QRScanView"
                                                      owner:self
                                                    options:nil];
    
    QRScanView* scanView = [ nibViews objectAtIndex: 0];
    scanView->m_pInterop = Eegeo_NEW(ExampleApp::QRScan::View::QRScanViewInterop)(messageBus,scanView);
    scanView.alpha = 0.f;
    scanView->m_stateChangeAnimationTimeSeconds = 0.2f;
    scanView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
    scanView.pCameraContentView.layer.cornerRadius = 10.0f;
    scanView.pViewforCameraLayer.layer.cornerRadius = 10.0f;
    return scanView;
}


- (void)dealloc
{

    [_pViewforCameraLayer release];
    [_pCaptureSession release];
    [_pVideoPreviewLayer release];
    [_pCameraContentView release];
    [self removeFromSuperview];
    Eegeo_DELETE m_pInterop;
    [super dealloc];
    
    
}

- (void)layoutSubviews
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const float boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
    
    const float mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    const float mainWindowHeight = boundsHeight * 0.9;

    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);

    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
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

- (IBAction)onCloseButtonTapped
{
    [self stopReading];
    _pIsReading = NO;
    m_pInterop->CloseTapped();
}

#pragma mark - Private Methods And QR Scanning

- (void)addOverlay
{
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:self.pViewforCameraLayer.frame];
    [imageView setImage:[UIImage imageNamed:@"scan_outline.png"]];
    [self.pCameraContentView.layer insertSublayer:imageView.layer above:_pVideoPreviewLayer];
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
    
    _pVideoPreviewLayer.cornerRadius = 10.0;

    [_pVideoPreviewLayer setVideoGravity:AVLayerVideoGravityResizeAspectFill];
    
    [_pVideoPreviewLayer setFrame:_pCameraContentView.layer.bounds];
    
    [_pCameraContentView.layer addSublayer:_pVideoPreviewLayer];
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();

    if (!isPhone)
    {
        _pVideoPreviewLayer.connection.videoOrientation = AVCaptureVideoOrientationLandscapeLeft;
    }

    [_pCaptureSession startRunning];
    
    [self addOverlay];
    
    return YES;
    
}


-(void)stopReading{
    
    [_pCaptureSession stopRunning];
    [_pCaptureSession release];
    _pCaptureSession = nil;
    
    [_pVideoPreviewLayer removeFromSuperlayer];
    [_pVideoPreviewLayer release];
    _pVideoPreviewLayer = nil;
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
                [self performSelectorOnMainThread:@selector(onQRScanCompleted:) withObject:qrString waitUntilDone:NO];
            }
            else                
            {
                //you can show your custom alert like - there is no HTTP link present in the QR Code. //
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
        
        NSURL *url  = [[NSURL alloc] initWithString:resultScanned];
        NSArray *pathComponents = [url pathComponents];

        if (pathComponents != nil && pathComponents.count >=6) // Currently assuming we will have 6 total path components
        {
            NSString *locationMode = pathComponents[1];
            if ([locationMode isEqualToString:@"indoor"] && pathComponents.count == 8) //7
            {
                double lat = [pathComponents[2] doubleValue];
                double lon = [pathComponents[3] doubleValue];
                NSString *indoorId = pathComponents[4];
                int floorIndex = [pathComponents[5] intValue];
                double orientation = [pathComponents[6] doubleValue];
                double zoomLevel = [pathComponents[7] doubleValue];
                
                m_pInterop->OnIndoorQRScanCompleted(lat,lon,[indoorId UTF8String],floorIndex,orientation,zoomLevel);
                m_pInterop->CloseTapped();
            }else if ([locationMode isEqualToString:@"outdoor"] && pathComponents.count == 6) //5
            {
                double lat = [pathComponents[2] doubleValue];
                double lon = [pathComponents[3] doubleValue];
                double orientation = [pathComponents[4] doubleValue];
                double zoomLevel = [pathComponents[5] doubleValue];

                m_pInterop->OnOutdoorQRScanCompleted(lat,lon,orientation,zoomLevel);
                m_pInterop->CloseTapped();
            }else
            {
                 [self notifyInvalidQRCode];
            }
        }else
        {
            [self notifyInvalidQRCode];
        }
    }
    else if (resultScanned == nil)
    {
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
