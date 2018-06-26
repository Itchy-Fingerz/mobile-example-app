//
//  InputValidationCodeViewController.m
//  ExampleApp
//
//  Created by Sohail Khan on 5/17/18.
//

#import "InputValidationCodeViewController.h"
#import "MZTimerLabel.h"
#import "ShowErrorMessageViewController.h"
#import "SVProgressHUD.h"


@interface InputValidationCodeViewController ()<UITextFieldDelegate>
{
    MZTimerLabel *timerLabelCounter;
    UITextField* passcodeTextField;

}
@property (retain, nonatomic) IBOutlet UITextField *validationCodeTextfield;
@property (retain, nonatomic) IBOutlet UITextField *verifyCodeTextfield1;
@property (retain, nonatomic) IBOutlet UITextField *verifyCodeTextfield2;
@property (retain, nonatomic) IBOutlet UITextField *verifyCodeTextfield3;
@property (retain, nonatomic) IBOutlet UITextField *verifyCodeTextfield4;
@property (retain, nonatomic) IBOutlet UIView *view1;
@property (retain, nonatomic) IBOutlet UIView *view2;
@property (retain, nonatomic) IBOutlet UIView *view3;
@property (retain, nonatomic) IBOutlet UIView *view4;

@property (retain, nonatomic) IBOutlet UILabel *validationMessageLabel;
@property (retain, nonatomic) IBOutlet UIButton *validateButton;
@property (retain, nonatomic) IBOutlet UILabel *timerLabel;
@property (retain, nonatomic) IBOutlet UILabel *pinLebel;

-(void)setupPasscodeTextField;

@end

@implementation InputValidationCodeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.pinLebel.text = [NSString stringWithFormat:@"Pin: %@",self.pin];
    [self setupTimer];
    [self setupPasscodeTextField];
    [super addTapGestureInView];
}
-(void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}
-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    [passcodeTextField becomeFirstResponder];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
#pragma mark Helpers
- (void) onTokenExpried
{
    UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"Code expired"
                                                                   message:@"Validation code has been expired"
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
                                                          handler:^(UIAlertAction * action) {
                                                              [self.navigationController popViewControllerAnimated:true];
                                                          }];
    
    [alert addAction:defaultAction];
    [self presentViewController:alert animated:YES completion:nil];
}
- (void) onResendCodeReceivedAlert:(NSDictionary *) dataDictionary
{

    UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"Success"
                                                                   message:@"Validation code has been resent"
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
                                                          handler:^(UIAlertAction * action) {
                                                              [passcodeTextField becomeFirstResponder];
                                                              self.token = [dataDictionary objectForKey:@"token"];
                                                              self.status = [dataDictionary objectForKey:@"status"];
                                                              self.pin = [dataDictionary objectForKey:@"pin"];
                                                              self.pinLebel.text = [NSString stringWithFormat:@"Pin: %@",self.pin];
                                                              [timerLabelCounter setCountDownTime:600];
                                                              [timerLabelCounter start];
                                                          }];
    
    [alert addAction:defaultAction];
    [self presentViewController:alert animated:YES completion:nil];
}
-(void)resetPassCode
{
    [self.verifyCodeTextfield1 setText:@""];
    [self.verifyCodeTextfield2 setText:@""];
    [self.verifyCodeTextfield3 setText:@""];
    [self.verifyCodeTextfield4 setText:@""];
    //self.view1.backgroundColor = [UIColor whiteColor];//[UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
    //self.view2.backgroundColor = [UIColor whiteColor];//[UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
    //self.view3.backgroundColor = [UIColor whiteColor];//[UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
    //self.view4.backgroundColor = [UIColor whiteColor];//[UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
    [self.validateButton setEnabled:false];
    
    [passcodeTextField setText:@""];
    self.validationMessageLabel.hidden = true;
}

-(void)resetPassCodeOnWrongValidationCode:(NSString *)errorMessage
{
    [self.verifyCodeTextfield1 setText:@""];
    [self.verifyCodeTextfield2 setText:@""];
    [self.verifyCodeTextfield3 setText:@""];
    [self.verifyCodeTextfield4 setText:@""];
    //self.view1.backgroundColor = [UIColor whiteColor];//[UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
    //self.view2.backgroundColor = [UIColor whiteColor];//[UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
    //self.view3.backgroundColor = [UIColor whiteColor];//[UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
    //self.view4.backgroundColor = [UIColor whiteColor];//[UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
    [self.validateButton setEnabled:false];
    
    [passcodeTextField setText:@""];
    [passcodeTextField becomeFirstResponder];
    self.validationMessageLabel.hidden = false;
    self.validationMessageLabel.text = errorMessage;
}
-(void)setupPasscodeTextField
{
    passcodeTextField = [[UITextField alloc] init];
    passcodeTextField.keyboardType = UIKeyboardTypeNumberPad;
    passcodeTextField.hidden = true;
    passcodeTextField.delegate = self;
    [self.view addSubview:passcodeTextField];
}
-(void) setupTimer
{
    timerLabelCounter = [[MZTimerLabel alloc] initWithLabel:self.timerLabel andTimerType:MZTimerLabelTypeTimer];
    [timerLabelCounter setCountDownTime:600];
    NSString* text = @"The validation code will expire in here";
    NSRange r = [text rangeOfString:@"here"];
    
    UIColor* fgColor = [UIColor colorWithRed:130.0/255 green:129.0/255 blue:129.0/255 alpha:1.0];
    NSDictionary* attributesForRange = @{
                                         NSForegroundColorAttributeName: fgColor,
                                         };
    timerLabelCounter.attributedDictionaryForTextInRange = attributesForRange;
    timerLabelCounter.text = text;
    timerLabelCounter.textRange = r;
    timerLabelCounter.timeFormat = @"mm:ss";
    timerLabelCounter.resetTimerAfterFinish = YES;
    [timerLabelCounter start];
    timerLabelCounter.endedBlock = ^(NSTimeInterval time) {
        [timerLabelCounter setCountDownTime:0];
        [self onTokenExpried];
    };
}

-(void) onVerifyCodeResponseReceived:(UNIHTTPJsonResponse*) response
{
    NSInteger code = response.code;
    if (code != 200)
    {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.view setUserInteractionEnabled:true];
            [SVProgressHUD dismiss];
            [self showAlertView:@"Error" withMessage:@"Please make sure you are connected to the internet"];
        });
        return;
    }
    UNIJsonNode *body = response.body;
    NSDictionary * responseDic = [body object];
    NSDictionary *dataDictionary = [responseDic objectForKey:@"data"];

    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSString * status = [dataDictionary objectForKey:@"status"];
        if ([status isEqualToString:@"STATUS_VERIFIED"])
        {
            [timerLabelCounter pause];
            [self performSegueWithIdentifier:@"showValidationSuccessVc" sender:nil];
        }
        else if ([status isEqualToString:@"STATUS_WRONG_CODE"])
        {
            
            [self resetPassCodeOnWrongValidationCode:[responseDic objectForKey:@"message"]];
        }
        else //if ([status isEqualToString:@"STATUS_ATTEMPTS_EXCEEDED"])
        {
            [timerLabelCounter pause];
            [self performSegueWithIdentifier:@"ShowExceedVC" sender:responseDic];
        }
        [self.view setUserInteractionEnabled:true];
        [SVProgressHUD dismiss];
    });
    
    
}

-(void) onSendSmsVerificationResponseReceived:(UNIHTTPJsonResponse*) response
{
    NSInteger code = response.code;
    if (code != 200)
    {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.view setUserInteractionEnabled:true];
            [SVProgressHUD dismiss];
            [self showAlertView:@"Error" withMessage:@"Please make sure you are connected to the internet"];
        });
        
        return;
    }
    UNIJsonNode *body = response.body;
    NSDictionary * mainResponseDictionary = [body object];
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSDictionary *dataDictionary = [mainResponseDictionary objectForKey:@"data"];
        NSString *status = [dataDictionary objectForKey:@"status"];
        if ([status isEqualToString:@"STATUS_IN_PROGRESS"])
        {
            [self onResendCodeReceivedAlert:dataDictionary];
        }
        else if ([status isEqualToString:@"STATUS_VERIFIED"])
        {
            [self performSegueWithIdentifier:@"showValidationSuccessVc" sender:nil]; // for testing perpose
        }
        else
        {
            [self performSegueWithIdentifier:@"ShowExceedVC" sender:[mainResponseDictionary objectForKey:@"message"]];
        }
        
        [self.view setUserInteractionEnabled:true];
        [SVProgressHUD dismiss];
    });
}

#pragma mark IBAction

- (IBAction)resendButtonPressed:(id)sender {
    [self resetPassCode];
    [timerLabelCounter reset];
    [timerLabelCounter pause];
    [SVProgressHUD show];
    [self.view setUserInteractionEnabled:false];
    [super sendSmsVerificationRequest:self.phoneNumber withCompletionHandler:^(UNIHTTPJsonResponse * response) {
        [self onSendSmsVerificationResponseReceived:response];
    }];


}
- (IBAction)validationButtonPressed:(id)sender {

    if ([passcodeTextField.text  length] != 4)
    {
        [self showAlertView:@"Error" withMessage:@"Please Enter  Validation Code"];
    }
    else
    {
        [SVProgressHUD show];
        [self.view setUserInteractionEnabled:false];
        if (self.token == nil)
        {
            self.token = @"";
        }
        [super sendVerifyCodeRequest:passcodeTextField.text token:self.token withCompletionHandler:^(UNIHTTPJsonResponse *response) {
            [self onVerifyCodeResponseReceived:response];
        }];
        
    }
}


#pragma mark UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    if (textField == passcodeTextField)
    {
        CGFloat moveY = -230.0f;
        if ([super isPhone])
        {
            moveY = -110.0f;
        }
        [self animateViewUpDown:moveY];
        return true;
    }
    else
    {
        if (![passcodeTextField isFirstResponder])
        {
            [self.verifyCodeTextfield1 setText:@""];
            [self.verifyCodeTextfield2 setText:@""];
            [self.verifyCodeTextfield3 setText:@""];
            [self.verifyCodeTextfield4 setText:@""];
            [passcodeTextField setText:@""];
            [self.validateButton setEnabled:false];
        }
        [passcodeTextField becomeFirstResponder];
        return false;
    }
}
- (BOOL)textFieldShouldEndEditing:(UITextField *)textField
{
    [self animateViewUpDown:0.0f];
    return true;
    
}


- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)replacementStr {

    if (textField == passcodeTextField)
    {
        
        NSInteger currentCharacterCount = textField.text.length;
        if (range.length + range.location > currentCharacterCount)
        {
            return false;
        }
        
        NSCharacterSet* nonNumbers = [[NSCharacterSet decimalDigitCharacterSet] invertedSet];
        NSRange r = [replacementStr rangeOfCharacterFromSet: nonNumbers];
        if (!(r.location == NSNotFound))
        {
            return false;
        }
        NSInteger newLength = currentCharacterCount + replacementStr.length - range.length;
        if (newLength <= 4)
        {
            if (range.location == 0 && ![replacementStr isEqualToString:@""])
            {
                self.verifyCodeTextfield1.text = [replacementStr substringFromIndex:[replacementStr length] - 1];
                //self.view1.backgroundColor = [UIColor colorWithRed:122.0/255.0 green:201/255.0 blue:67/255.0 alpha:1];
            }
            else if (range.location == 1 && ![replacementStr isEqualToString:@""])
            {
                self.verifyCodeTextfield2.text = [replacementStr substringFromIndex:[replacementStr length] - 1];
                //self.view2.backgroundColor = [UIColor colorWithRed:122.0/255.0 green:201/255.0 blue:67/255.0 alpha:1];
            }
            else if (range.location == 2 && ![replacementStr isEqualToString:@""])
            {
                self.verifyCodeTextfield3.text = [replacementStr substringFromIndex:[replacementStr length] - 1];
                //self.view3.backgroundColor = [UIColor colorWithRed:122.0/255.0 green:201/255.0 blue:67/255.0 alpha:1];
                
            }
            else if (range.location == 3 && ![replacementStr isEqualToString:@""])
            {
                self.verifyCodeTextfield4.text = [replacementStr substringFromIndex:[replacementStr length] - 1];
                //self.view4.backgroundColor = [UIColor colorWithRed:122.0/255.0 green:201/255.0 blue:67/255.0 alpha:1];
                
            }
            else if (range.location == 0 && [replacementStr isEqualToString:@""])
            {
                self.verifyCodeTextfield1.text = @"";
                //self.view1.backgroundColor = [UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
                
            }
            else if (range.location == 1 && [replacementStr isEqualToString:@""])
            {
                self.verifyCodeTextfield2.text = @"";
                //self.view2.backgroundColor = [UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
                
            }
            else if (range.location == 2 && [replacementStr isEqualToString:@""])
            {
                self.verifyCodeTextfield3.text = @"";
                //self.view3.backgroundColor = [UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
                
            }
            else if (range.location == 3 && [replacementStr isEqualToString:@""])
            {
                self.verifyCodeTextfield4.text = @"";
                //self.view4.backgroundColor = [UIColor colorWithRed:171.0/255.0 green:172.0/255.0 blue:173.0/255.0 alpha:1];
                
            }
            if ([replacementStr isEqualToString:@""])
            {
                [self.validateButton setEnabled:false];
                
            }
            if (newLength == 4)
            {
                passcodeTextField.text = [passcodeTextField.text stringByAppendingString: replacementStr];
                [passcodeTextField resignFirstResponder];
                [self.validateButton setEnabled:true];
                
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}



#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
    if ([segue.identifier isEqualToString:@"ShowExceedVC"])
    {
        ShowErrorMessageViewController *destinationVC = (ShowErrorMessageViewController *) [segue destinationViewController];
        NSDictionary *mainResponseDictionary = (NSDictionary *) sender;
        destinationVC.errorMessage = [mainResponseDictionary objectForKey:@"message"];
    }
}


- (void)dealloc {
    if (timerLabelCounter != nil )
    {
        [timerLabelCounter release];
    }
    [_pin release];
    [_phoneNumber retain];
    [passcodeTextField release];
    [_verifyCodeTextfield1 release];
    [_verifyCodeTextfield2 release];
    [_verifyCodeTextfield3 release];
    [_verifyCodeTextfield4 release];
    [_status release];
    [_token release];
    [_validationMessageLabel release];
    [_validationCodeTextfield release];
    [_validateButton release];
    [_timerLabel release];
    [_view1 release];
    [_view2 release];
    [_view3 release];
    [_view4 release];
    [_pinLebel release];
    [super dealloc];
}
@end
