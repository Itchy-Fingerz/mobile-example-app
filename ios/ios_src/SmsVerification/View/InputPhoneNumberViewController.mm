//
//  SMSVerificationViewController.m
//  ExampleApp
//
//  Created by Sohail Khan on 5/17/18.
//

#import "InputPhoneNumberViewController.h"
#import "UNIRest.h"
#import "InputValidationCodeViewController.h"
#import "ShowErrorMessageViewController.h"
#import "SVProgressHUD.h"
#import "ValidationSucessViewController.h"


@interface InputPhoneNumberViewController ()
@property (retain, nonatomic) IBOutlet UITextField *usernameTextfield;
@property (retain, nonatomic) IBOutlet UITextField *passwordTextfield;
@property (retain, nonatomic) IBOutlet UIButton *verifyButton;
@property (retain, nonatomic) IBOutlet UILabel *errorLabel;

@end

@implementation InputPhoneNumberViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [super addTapGestureInView];
    [self.verifyButton setEnabled:false];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
    
    if ([segue.identifier isEqualToString:@"showValidationSuccessVc"])
    {
        ValidationSucessViewController * destinationVC = (ValidationSucessViewController *) [segue destinationViewController];
        destinationVC.sucessMessage = @"Login Successful!";
    }
}


- (void)dealloc {
    [_usernameTextfield release];
    [_passwordTextfield release];
    [_verifyButton release];
    [_errorLabel release];
    [super dealloc];
}

#pragma mark IBACtion

- (IBAction)verfiyButtonPressed:(id)sender {
    if (![self isNumberValid])
    {
        self.errorLabel.text = @"Entered invalid phone number";
        self.errorLabel.hidden = false;
    }
    else
    {
        self.errorLabel.hidden = true;
        [SVProgressHUD show];
        [self.view setUserInteractionEnabled:false];
        //@"admin@mail.me"
        //@"admin"
        [super loginRequest:self.usernameTextfield.text Password:self.passwordTextfield.text withCompletionHandler:^(UNIHTTPJsonResponse * response) {
            [self onResponseReceived:response];
        }];
        
    }
    
}


#pragma mark UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (textField == self.usernameTextfield)
    {
        //[textField resignFirstResponder];
        [self.passwordTextfield becomeFirstResponder];
    }
    else if (textField == self.passwordTextfield)
    {
        [textField resignFirstResponder];
        if ([self isNumberValid])
        {
            [self verfiyButtonPressed:self.verifyButton];
        }

    }
    return YES;
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{

    return true;
}
- (BOOL)textFieldShouldEndEditing:(UITextField *)textField
{
    if (![self isNumberValid])
    {
        [self.verifyButton setEnabled:false];
    }
    else
    {
        [self.verifyButton setEnabled:true];
    }
    return true;

}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    CGFloat moveY = -310.0f;
    if ([super isPhone])
    {
        moveY = -150.0f;
    }
    [self animateViewUpDown:moveY];

}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
    [self animateViewUpDown:0.0f];

}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)replacementStr
{
    return true;
}


#pragma mark UI Mehtods
-(bool) isNumberValid
{
    return (![self.usernameTextfield.text isEqualToString:@""] && ![self.passwordTextfield.text isEqualToString:@""] && [self validateEmailWithString:self.usernameTextfield.text]);
}
-(void) setUpUi{
    self.usernameTextfield.leftViewMode = UITextFieldViewModeAlways;
    self.usernameTextfield.leftView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 10)];
    self.passwordTextfield.leftViewMode = UITextFieldViewModeAlways;
    self.passwordTextfield.leftView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 10)];
}

- (BOOL)validateEmailWithString:(NSString*)email
{
    NSString *emailRegex = @"[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}";
    NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", emailRegex];
    return [emailTest evaluateWithObject:email];
}

-(void) onResponseReceived:(UNIHTTPJsonResponse*) response
{
    NSInteger code = response.code;
    UNIJsonNode *body = response.body;
    NSDictionary * mainResponseDictionary = [body object];
    if (code != 200)
    {
        dispatch_async(dispatch_get_main_queue(), ^{
            if (mainResponseDictionary == nil)
            {
                [self showAlertView:@"Error" withMessage:@"Please make sure you are connected to the internet"];
            }
            else
            {
                self.errorLabel.text = [mainResponseDictionary objectForKey:@"error_description"];
                self.errorLabel.hidden = false;
            }
            [SVProgressHUD dismiss];
            [self.view setUserInteractionEnabled:true];

        });

        return;
    }

    dispatch_async(dispatch_get_main_queue(), ^{

        if ([[mainResponseDictionary objectForKey:@"expires_in"] intValue] >= 0 && [mainResponseDictionary objectForKey:@"access_token"] != nil)
        {
            [self performSegueWithIdentifier:@"showValidationSuccessVc" sender:nil];
        }
        else if (![[mainResponseDictionary objectForKey:@"error_description"] isEqual:[NSNull null]])
        {
            self.errorLabel.text = [mainResponseDictionary objectForKey:@"error_description"];
            self.errorLabel.hidden = false;
        }
        [self.view setUserInteractionEnabled:true];
        [SVProgressHUD dismiss];
    });
}


@end
