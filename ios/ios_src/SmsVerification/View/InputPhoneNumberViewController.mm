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


@interface InputPhoneNumberViewController ()

@property (retain, nonatomic) IBOutlet UITextField *phoneNumberTextField;
@property (retain, nonatomic) IBOutlet UIButton *verifyButton;
-(void) addToolBarInPhoneNumberTextField;
@property (retain, nonatomic) IBOutlet UILabel *errorLabel;

@end

@implementation InputPhoneNumberViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [super addTapGestureInView];
    [self addToolBarInPhoneNumberTextField];
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
    
    if ([segue.identifier isEqualToString:@"ShowInputValidationCodeVC"])
    {
        InputValidationCodeViewController *destinationVC = (InputValidationCodeViewController *) [segue destinationViewController];
        NSDictionary *dataDictionry = (NSDictionary *) sender;
        destinationVC.token = [dataDictionry objectForKey:@"token"];
        destinationVC.status = [dataDictionry objectForKey:@"status"];
        destinationVC.pin = [dataDictionry objectForKey:@"pin"];
        destinationVC.phoneNumber = self.phoneNumberTextField.text;
    }
    else if ([segue.identifier isEqualToString:@"ShowExceedVC"])
    {
        ShowErrorMessageViewController *destinationVC = (ShowErrorMessageViewController *) [segue destinationViewController];
        NSDictionary *mainResponseDictionary = (NSDictionary *) sender;
        destinationVC.errorMessage = [mainResponseDictionary objectForKey:@"message"];

    }
}


- (void)dealloc {
    [_phoneNumberTextField release];
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
       // NSString *mockNumber = @"+971545764132";
        //NSString *testStr = self.phoneNumberTextField.text;
        [super sendSmsVerificationRequest:[NSString stringWithFormat:@"+971%@",self.phoneNumberTextField.text] withCompletionHandler:^(UNIHTTPJsonResponse * response) {
            [self onResponseReceived:response];
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
    CGFloat moveY = -230.0f;
    if ([super isPhone])
    {
        moveY = -110.0f;
    }
    [self animateViewUpDown:moveY];
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
    [self animateViewUpDown:0.0f];
    return true;

}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)replacementStr
{
    NSCharacterSet* nonNumbers = [[NSCharacterSet decimalDigitCharacterSet] invertedSet];
    NSRange r = [replacementStr rangeOfCharacterFromSet: nonNumbers];
    if (!(r.location == NSNotFound))
    {
        return false;
    }
    if (self.phoneNumberTextField.text.length >= 9 && ![replacementStr isEqualToString:@""])
    {
        return false;
    }
    return true;
}


#pragma mark UI Mehtods
-(bool) isNumberValid
{
    return (self.phoneNumberTextField.text.length == 9);//(self.phoneNumberTextField.text.length < 3 || self.phoneNumberTextField.text.length > 10);
}
-(void) setUpUi{
    self.phoneNumberTextField.leftViewMode = UITextFieldViewModeAlways;
    self.phoneNumberTextField.leftView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 10)];
}

-(void) addToolBarInPhoneNumberTextField
{
    if ([super isPhone])
    {
        UIToolbar* keyboardToolbar = [[UIToolbar alloc] init];
        [keyboardToolbar sizeToFit];
        UIBarButtonItem *flexBarButton = [[UIBarButtonItem alloc]
                                          initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace
                                          target:nil action:nil];
        UIBarButtonItem *doneBarButton = [[UIBarButtonItem alloc]
                                          initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                          target:self action:@selector(textViewDoneButtonPressed)];
        keyboardToolbar.items = @[flexBarButton, doneBarButton];
        self.phoneNumberTextField.inputAccessoryView = keyboardToolbar;
        
        [keyboardToolbar release];
        [flexBarButton release];
        [doneBarButton release];
    }
}

-(void)textViewDoneButtonPressed
{
    [self.phoneNumberTextField resignFirstResponder];
}




-(void) onResponseReceived:(UNIHTTPJsonResponse*) response
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

        NSDictionary *dataDictioary = [mainResponseDictionary objectForKey:@"data"];
        NSString *status = [dataDictioary objectForKey:@"status"];
        if ([status isEqualToString:@"STATUS_IN_PROGRESS"])
        {
            [self performSegueWithIdentifier:@"ShowInputValidationCodeVC" sender:dataDictioary];
        }
        else if ([status isEqualToString:@"STATUS_VERIFIED"])
        {
            [self performSegueWithIdentifier:@"showValidationSuccessVc" sender:nil];
        }
        else if ([status isEqualToString:@"STATUS_BLOCKED"])
        {
            [self performSegueWithIdentifier:@"ShowExceedVC" sender:mainResponseDictionary];
        }
        else
        {
            //[self performSegueWithIdentifier:@"ShowExceedVC" sender:mainResponseDictionary];
            self.errorLabel.text = [mainResponseDictionary objectForKey:@"message"];
            self.errorLabel.hidden = false;
        }
        [self.view setUserInteractionEnabled:true];
        [SVProgressHUD dismiss];
    });
}


@end
