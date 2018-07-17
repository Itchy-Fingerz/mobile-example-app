//
//  SmsValidationBaseViewController.h
//  ExampleApp
//
//  Created by Sohail Khan on 5/22/18.
//

#import <UIKit/UIKit.h>
#import "UNIRest.h"

@interface SmsValidationBaseViewController : UIViewController
{
    
}
@property (retain, nonatomic) IBOutlet UIActivityIndicatorView *spiner;
-(void)sendSmsVerificationRequest:(NSString *)preNumber phoneNumber:(NSString *)phoneNumber withCompletionHandler:(void(^)(UNIHTTPJsonResponse *))handlerBlock;
-(void)sendVerifyCodeRequest:(NSString *)preNumber phoneNumber:(NSString *)phoneNumber code:(NSString *)code withCompletionHandler:(void(^)(UNIHTTPJsonResponse *))handlerBlock;
-(void) animateViewUpDown:(CGFloat) yPosition;
-(void)showAlertView:(NSString*)title withMessage:(NSString*)message;
-(void) addTapGestureInView;
-(BOOL) isPhone;
@end
