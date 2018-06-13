//
//  InputValidationCodeViewController.h
//  ExampleApp
//
//  Created by Sohail Khan on 5/17/18.
//

#import <UIKit/UIKit.h>
#import "SmsValidationBaseViewController.h"

@interface InputValidationCodeViewController : SmsValidationBaseViewController

@property (nonatomic,retain) NSString *token;
@property (nonatomic,retain) NSString *status;
@property (nonatomic,retain) NSString *phoneNumber;
@property (nonatomic,retain) NSString *pin;

@end
