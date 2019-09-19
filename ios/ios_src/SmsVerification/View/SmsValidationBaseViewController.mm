//
//  SmsValidationBaseViewController.m
//  ExampleApp
//
//  Created by Sohail Khan on 5/22/18.
//

#import "SmsValidationBaseViewController.h"
#import "LolayKeychain.h"
#import "SVProgressHUD.h"
#import "NSMutableURLRequest+BasicAuth.h"



#define BASE_URL_SMS_VERIFICATION @"https://dev-services.smartcitti.com/oauth/token?username=%@&password=%@&grant_type=password"
#define END_POINT_SEND_SMS @"app/system/sendCode"
#define END_POINT_VERIFY_CODE @"oa/codeEmployeeLogin"
#define REQUEST_HEADER_NAME @"Content-Type"
#define REQUEST_HEADER_VALUE @"application/json"

@interface SmsValidationBaseViewController ()

@end

@implementation SmsValidationBaseViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self.spiner stopAnimating];
    [SVProgressHUD setBackgroundColor:[UIColor clearColor]];
    [SVProgressHUD setForegroundColor:[UIColor colorWithRed:75/255.0 green:74/255.0 blue:72/255.0 alpha:1.0]];
    [SVProgressHUD setDefaultMaskType:SVProgressHUDMaskTypeBlack];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (void)dealloc {
    [_spiner release];
    [super dealloc];
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
#pragma mark API CALLS
-(void)loginRequest:(NSString *)userName Password:(NSString *)password withCompletionHandler:(void(^)(UNIHTTPJsonResponse *))handlerBlock
{
    NSString * url = [NSString stringWithFormat:BASE_URL_SMS_VERIFICATION,userName,password];
    NSMutableURLRequest *authRequest = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:url]];
    [NSMutableURLRequest basicAuthForRequest:authRequest withUsername:@"smolly" andPassword:@"g3n3r4l53cr3t"];
    NSLog(@"OAuth Header %@",[authRequest valueForHTTPHeaderField:@"Authorization"]);
    NSDictionary *headers = @{@"Authorization":[authRequest valueForHTTPHeaderField:@"Authorization"]};

    [[UNIRest post:^(UNISimpleRequest *request) {
        [request setUrl:url];
        [request setHeaders:headers];
    }] asJsonAsync:^(UNIHTTPJsonResponse* response, NSError *error) {
        // This is the asyncronous callback block
        handlerBlock(response);
    }];
}

-(void)sendVerifyCodeRequest:(NSString *)preNumber phoneNumber:(NSString *)phoneNumber code:(NSString *)code withCompletionHandler:(void(^)(UNIHTTPJsonResponse *))handlerBlock
{
    NSDictionary *headers = @{REQUEST_HEADER_NAME: REQUEST_HEADER_VALUE};
    NSDictionary *parameters = @{@"code": code, @"pre" : preNumber,@"mobi":phoneNumber};
    NSString * url = [NSString stringWithFormat:@"%@%@",BASE_URL_SMS_VERIFICATION,END_POINT_VERIFY_CODE];
    [[UNIRest post:^(UNISimpleRequest *request) {
        [request setUrl:url];
        [request setHeaders:headers];
        [request setParameters:parameters];
    }] asJsonAsync:^(UNIHTTPJsonResponse* response, NSError *error) {
        handlerBlock(response);
    }];
}

#pragma mark UI

-(NSString *) getDeviceUUID
{
    
    NSString *uuid = [LolayKeychain stringForKey:@"device_uuid"];
    if (uuid == nil)
    {
        uuid = [[NSUUID UUID] UUIDString];
        [LolayKeychain save:uuid forKey:@"device_uuid"];
    }
    //NSString *uuid = [[TAKUUIDStorage sharedInstance] findOrCreate];
    
    return uuid;
}
-(BOOL) isPhone
{
    return (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone);
}
-(void) addTapGestureInView
{
    UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleTapFrom:)];
    [self.view addGestureRecognizer:tapGestureRecognizer];
    [tapGestureRecognizer release];
}
- (void) handleTapFrom: (UITapGestureRecognizer *)recognizer
{
    //Code to handle the gesture
    [self.view endEditing:true];
}
-(void) animateViewUpDown:(CGFloat) yPosition
{
    [UIView animateWithDuration:0.3 animations:^{
        CGRect f = self.view.frame;
        f.origin.y = yPosition;
        self.view.frame = f;
    }];
}

-(void)showAlertView:(NSString*)title withMessage:(NSString*)message
{
    
    UIAlertController * alert = [UIAlertController
                                 alertControllerWithTitle:title
                                 message:message
                                 preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction* okButton = [UIAlertAction
                               actionWithTitle:@"OK"
                               style:UIAlertActionStyleDefault
                               handler:^(UIAlertAction * action) {
                               }];
    
    [alert addAction:okButton];
    [self presentViewController:alert animated:true completion:^{
        
    }];
}

@end