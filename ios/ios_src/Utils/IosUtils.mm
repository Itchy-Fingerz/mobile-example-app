// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IosUtils.h"
#include "Utils.h"

namespace ExampleApp
{
    namespace Utils
    {
        IosUtils::IosUtils()
        {
            
        }

        IosUtils::~IosUtils()
        {

        }
        
        void IosUtils::OpenARApplication()
        {
            NSString *customURL = @"eagleAr://";
            UIApplication *application = [UIApplication sharedApplication];
            NSURL *URL = [NSURL URLWithString:customURL];
            
            if ([application canOpenURL:URL]) {
                // Safe to launch the AR App app
                [application openURL:URL];
            }
            else
            {
                IosUtils::notifyAppNotInstalled();
            }
        }
        
        void IosUtils::notifyAppNotInstalled()
        {
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Error" message:@"Eagle AR app is not installed on your device." preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *ok = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                
            }];
            [alert addAction:ok];
            
            UIWindow *window = [[UIApplication sharedApplication] keyWindow];
            UIViewController *viewController = window.rootViewController;
            [viewController presentViewController:alert animated:YES completion:nil];
        }
    }
}
