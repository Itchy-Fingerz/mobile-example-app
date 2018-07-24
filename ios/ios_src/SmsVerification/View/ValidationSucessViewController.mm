//
//  ValidationSucessViewController.m
//  ExampleApp
//
//  Created by Sohail Khan on 5/17/18.
//

#import "ValidationSucessViewController.h"
#import "AppDelegate.h"
#import "SVProgressHUD.h"

@interface ValidationSucessViewController ()
@property (retain, nonatomic) IBOutlet UILabel *messageLabel;
@property (retain, nonatomic) IBOutlet UIButton *doneButton;
@property (retain, nonatomic) IBOutlet UIActivityIndicatorView *spiner;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *topConstraintLogo;

@end

@implementation ValidationSucessViewController

-(void) viewWillLayoutSubviews
{
    [super viewWillLayoutSubviews];
    
    if (self.view.frame.size.height <= 568)
    {
        self.topConstraintLogo.constant = 30;
    }
}
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.navigationItem.hidesBackButton = YES;
    self.doneButton.semanticContentAttribute = UISemanticContentAttributeForceRightToLeft;
    self.messageLabel.text = self.sucessMessage;

}

-(void) viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [SVProgressHUD dismiss];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)doneButtonPressedL:(id)sender {
    
    [SVProgressHUD show];
    //[self.spiner startAnimating];
    [self performSelector:@selector(setRootViewController) withObject:nil afterDelay:0.1];
}

-(void) setRootViewController
{
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"isVerified"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    [[NSNotificationCenter defaultCenter] postNotificationName: @"setAppRootViewController"
                                                        object: nil
                                                      userInfo: nil];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)dealloc {
    [_messageLabel release];
    [_doneButton release];
    [_spiner release];
    [super dealloc];
}
@end
