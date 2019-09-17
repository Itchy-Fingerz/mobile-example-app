//
//  ExceedAttemptViewController.m
//  ExampleApp
//
//  Created by Sohail Khan on 5/17/18.
//

#import "ShowErrorMessageViewController.h"

@interface ShowErrorMessageViewController ()
@property (retain, nonatomic) IBOutlet UILabel *attemptsExceedLabel;

@end

@implementation ShowErrorMessageViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.navigationItem.hidesBackButton = YES;
    self.attemptsExceedLabel.text = self.errorMessage;

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)goBackButtonPressed:(id)sender {
    [self.navigationController popToRootViewControllerAnimated:true];
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
    [_errorMessage release];
    [_attemptsExceedLabel release];
    [super dealloc];
}
@end
