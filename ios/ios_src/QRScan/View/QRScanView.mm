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
    
    if ([UIScreen mainScreen].bounds.size.height>=667)
    {
        scanView.pUseCameraLabel.numberOfLines = 0;
    }
    else
    {
        scanView.pUseCameraLabel.numberOfLines = 2;
    }
    
    if ([UIScreen mainScreen].bounds.size.width == 320)
    {
        
        [scanView.pUseCameraLabel setFont: [scanView.pUseCameraLabel.font fontWithSize: 10.f]];
        [scanView.pQrdetactedLabel setFont: [scanView.pQrdetactedLabel.font fontWithSize: 10.f]];
        [scanView.pTransitionLabel setFont: [scanView.pTransitionLabel.font fontWithSize: 10.f]];
    }
    
    [[NSNotificationCenter defaultCenter]addObserver:scanView selector:@selector(OrientationDidChange:) name:UIDeviceOrientationDidChangeNotification object:nil];
    
    [scanView.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];

    return scanView;
}


- (void)dealloc
{

    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIDeviceOrientationDidChangeNotification
                                                  object:nil];
    
    [_pViewforCameraLayer release];
    [_pCaptureSession release];
    [_pVideoPreviewLayer release];
    [_pCameraContentView release];
    [self removeFromSuperview];
    Eegeo_DELETE m_pInterop;
    [_pQrDetectedImageView release];
    [_pCloseButton release];
    [_pUseCameraLabel release];
    [_pQrdetactedLabel release];
    [_pTransitionLabel release];
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
    [_pQrDetectedImageView setHidden:true];
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
        UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
        
        if(orientation == UIDeviceOrientationLandscapeLeft)
        {
             _pVideoPreviewLayer.connection.videoOrientation = AVCaptureVideoOrientationLandscapeRight;
        }
        else if(orientation == UIDeviceOrientationLandscapeRight)
        {
             _pVideoPreviewLayer.connection.videoOrientation = AVCaptureVideoOrientationLandscapeLeft;
        }
       
    }

    [_pCaptureSession startRunning];
    
    [self addOverlay];
    
    return YES;
    
}

-(void)OrientationDidChange:(NSNotification*)notification
{
    UIDeviceOrientation orientation=[[UIDevice currentDevice]orientation];
    if(_pVideoPreviewLayer && orientation == UIDeviceOrientationLandscapeLeft)
    {
        _pVideoPreviewLayer.connection.videoOrientation = AVCaptureVideoOrientationLandscapeRight;
    }
    else if(_pVideoPreviewLayer && orientation == UIDeviceOrientationLandscapeRight)
    {
        _pVideoPreviewLayer.connection.videoOrientation = AVCaptureVideoOrientationLandscapeLeft;
    }
}
-(void)stopCaptureSession{
    [_pCaptureSession stopRunning];
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
    if (!_pIsScanningDone)
    {
        _pIsScanningDone = true;
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);//http://iphonedevwiki.net/index.php/AudioServices
    }
    
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
                [self performSelectorOnMainThread:@selector(onQRScanCompleted:) withObject:nil waitUntilDone:NO];
            }
            
        }
        
    }
}

-(void)onQRScanCompleted:(NSString *)resultScanned
{
    if (resultScanned != nil && _pIsReading)
    {
        _pIsReading = NO;
        
        NSURL *url  = [[NSURL alloc] initWithString:resultScanned];
        NSArray *pathComponents = [url pathComponents];

        if (pathComponents != nil && pathComponents.count >=7) // Currently assuming we will have 6 total path components
        {
            NSString *locationMode = pathComponents[1];
            NSString *buildingID = pathComponents[4];
            if ([locationMode isEqualToString:@"indoor"] && [buildingID isEqualToString:@"EIM-1daffd08-49d0-476d-866f-23a52f45713c"] && pathComponents.count == 9)
            {
                [_pQrDetectedImageView setHidden:false];
                _pIsScanningDone = false;
                [self stopCaptureSession];
                [self performSelector:@selector(dismissViewWithDelay:) withObject:pathComponents afterDelay:1.0];
            }else if ([locationMode isEqualToString:@"outdoor"] && pathComponents.count == 7)
            {
                [_pQrDetectedImageView setHidden:false];
                _pIsScanningDone = false;
                [self stopCaptureSession];
                [self performSelector:@selector(dismissViewWithDelay:) withObject:pathComponents afterDelay:1.0];
                
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

- (void) dismissViewWithDelay:(NSArray*)pathComponents
{
    NSString *locationMode = pathComponents[1];
    if ([locationMode isEqualToString:@"indoor"] && pathComponents.count == 9)
    {
        double lat = [pathComponents[2] doubleValue];
        double lon = [pathComponents[3] doubleValue];
        NSString *indoorId = pathComponents[4];
        int floorIndex = [pathComponents[5] intValue];
        double orientation = [pathComponents[6] doubleValue];
        double zoomLevel = [pathComponents[7] doubleValue];
        double tiltInDegree = [pathComponents[8] doubleValue];
        
        m_pInterop->CloseTapped();

        m_pInterop->OnIndoorQRScanCompleted(lat,lon,[indoorId UTF8String],floorIndex,orientation,zoomLevel,tiltInDegree);
        
    }else if ([locationMode isEqualToString:@"outdoor"] && pathComponents.count == 7)
    {
        double lat = [pathComponents[2] doubleValue];
        double lon = [pathComponents[3] doubleValue];
        double orientation = [pathComponents[4] doubleValue];
        double zoomLevel = [pathComponents[5] doubleValue];
        double tiltInDegree = [pathComponents[6] doubleValue];
        
        m_pInterop->CloseTapped();

        m_pInterop->OnOutdoorQRScanCompleted(lat,lon,orientation,zoomLevel,tiltInDegree);
        
    }
    [self stopReading];

}
- (void) notifyInvalidQRCode
{
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"QR Scan Error" message:@"It is not a valid QR Code." preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *ok = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        _pIsScanningDone = false;
    }];
    [alert addAction:ok];

    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    UIViewController *viewController = window.rootViewController;
    [viewController presentViewController:alert animated:YES completion:nil];
}


@end
