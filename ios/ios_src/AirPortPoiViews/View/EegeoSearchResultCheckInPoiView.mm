// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlightResultModel.h"
#import "EegeoSearchResultCheckInPoiView.h"
#import "EegeoSearchResultFlightTimingTableViewCell.h"

@interface EegeoSearchResultCheckInPoiView()
{
    IBOutlet UITableView *m_pFlightTimingTableView;
    ExampleApp::Search::SdkModel::SearchResultModel m_pCurrentModel;
    std::vector<ExampleApp::Search::SdkModel::FlightResultModel> m_flightsVector;
    IBOutlet UILabel *m_pBoardingTimeLabel;
    IBOutlet UILabel *m_pDepartingLabel;

    IBOutlet UILabel *m_pBoardingTimeCountDown;
    IBOutlet UILabel *m_pDepartingTimeCountDown;
    
    NSTimer *m_pContDownTimer;
    NSInteger m_boardingTimeLeft;
    NSInteger m_departureTimeLeft;

    
}
-(void) FlightListFromSearchResult;
@end
@implementation EegeoSearchResultCheckInPoiView

-(NSInteger)GetTimeDifferenc:(NSString*)timeStr
{
    NSDate *currentTime = [NSDate date];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd"];
    NSString *currentDateString = [dateFormatter stringFromDate:currentTime];
    NSString *boardingtimeDateString = [NSString stringWithFormat:@"%@ %@",currentDateString,timeStr];
    [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm"];
    
    NSDate *boardingTime = [dateFormatter dateFromString:boardingtimeDateString];
    NSTimeInterval distanceBetweenDates = [boardingTime timeIntervalSinceDate:currentTime];
    return distanceBetweenDates;
}

-(void) FlightListFromSearchResult
{
    rapidjson::Document json;
    std::string highlightedRoomId = "";
    
    m_flightsVector.clear();
    
    std::string airLineName = "";
    std::string flightCode = "";
    NSString *title = [NSString stringWithUTF8String:m_pCurrentModel.GetTitle().c_str()];
    
    if([title containsString:@"Delta"] )
    {
        airLineName = "Delta";
        flightCode = "DL";
    }
    else if ([title containsString:@"JetBlue"])
    {
        airLineName = "JetBlue";
        flightCode = "JBU";
    }
    else if ([title containsString:@"United"])
    {
        airLineName = "United";
        flightCode = "UT";
    }
    else if ([title containsString:@"Virgin"])
    {
        airLineName = "Virgin";
        flightCode = "VX";
    }
    
    ExampleApp::Search::SdkModel::FlightResultModel flightModel(airLineName,flightCode + " 395","Paris","130","11:54","12:34");
    m_flightsVector.push_back(flightModel);
    
    
    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 396","Chicago","131","12:04","12:34"));
    
    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 397","Amsterdam","132","12:14","12:34"));
    
    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 398","Lima","133","12:24","12:34"));
    
    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 399","New York","134","12:34","12:34"));

    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 400","Dusseldorf","135","12:44","12:34"));

    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 401","San Salvidor","136","12:54","12:34"));

    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 402","Guatemala Cty","137","13:04","12:34"));

    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 403","Beijing","138","13:14","12:34"));

    m_flightsVector.push_back(ExampleApp::Search::SdkModel::FlightResultModel(airLineName,flightCode + " 404","Hong Kong","139","13:24","12:34"));


}

-(void) updateCountdown {
    NSInteger hours, minutes, seconds;
    
    m_boardingTimeLeft--;
    m_departureTimeLeft--;
    if(m_boardingTimeLeft>0)
    {
        hours = m_boardingTimeLeft / 3600;
        minutes = (m_boardingTimeLeft % 3600) / 60;
        seconds = (m_boardingTimeLeft %3600) % 60;
        if (hours >= 1)
        {
            m_pBoardingTimeCountDown.text = [NSString stringWithFormat:@"%02ldhr:%02ld min", (long)hours, (long)minutes];
        }
        else
        {
            m_pBoardingTimeCountDown.text = [NSString stringWithFormat:@"%02ld min", (long)minutes];
        }
    }
    else
    {
        m_pBoardingTimeCountDown.hidden = true;
    }
    if(m_departureTimeLeft>0)
    {
        hours = m_departureTimeLeft / 3600;
        minutes = (m_departureTimeLeft % 3600) / 60;
        seconds = (m_departureTimeLeft %3600) % 60;
        if (hours >= 1)
        {
            m_pDepartingTimeCountDown.text = [NSString stringWithFormat:@"%02ldhr:%02ld min", (long)hours, (long)minutes];
        }
        else
        {
            m_pDepartingTimeCountDown.text = [NSString stringWithFormat:@"%02ld min", (long)minutes];

        }
    }
    else
    {
        m_pDepartingTimeCountDown.hidden = true;

    }
    
    if(m_boardingTimeLeft<0 && m_departureTimeLeft<0)
    {
        [m_pContDownTimer invalidate];
        m_pContDownTimer = nil;
        
    }

}
- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    m_pCurrentModel = *pModel;
    
    self.pTitleLbl.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    
    [self FlightListFromSearchResult];
    for(int i=0;i<m_flightsVector.size();i++)
    {
        ExampleApp::Search::SdkModel::FlightResultModel flightInfo = m_flightsVector[i];
        if(flightInfo.GetGateNo() == "134")
        {
            m_pDepartingLabel.text = [NSString stringWithUTF8String:flightInfo.GetFlightTime().c_str()];
            
            m_pBoardingTimeLabel.text = [NSString stringWithUTF8String:flightInfo.GetFlightBoardingTime().c_str()];
            if(m_pContDownTimer != nil)
            {
                [m_pContDownTimer invalidate];
                m_pContDownTimer = nil;
            }
            m_boardingTimeLeft = [self GetTimeDifferenc:[NSString stringWithUTF8String:flightInfo.GetFlightBoardingTime().c_str()]];
            m_departureTimeLeft = [self GetTimeDifferenc:[NSString stringWithUTF8String:flightInfo.GetFlightTime().c_str()]];
            if(m_boardingTimeLeft>0 || m_departureTimeLeft>0)
            {
                m_pContDownTimer = [NSTimer scheduledTimerWithTimeInterval: 1.0 target:self selector:@selector(updateCountdown) userInfo:nil repeats: YES];
            }

            break;
            
        }
    }
    [m_pFlightTimingTableView reloadData];
    
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
}

- (void) setFullyActive
{
    [m_pController setView:self];
    if(self.alpha == 1.f)
    {
        return;
    }
    
    [self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
    [m_pController setView:nil];
    if(self.alpha == 0.f)
    {
        return;
    }
    
    [self animateToAlpha:0.f];
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
     }];
}

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)getInterop
{
    return m_pInterop;
}

+(EegeoSearchResultCheckInPoiView *)EegeoSearchResultCheckInPoiViewWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop
{
    
    EegeoSearchResultCheckInPoiView *poiView = (EegeoSearchResultCheckInPoiView*)[[[NSBundle mainBundle] loadNibNamed:@"CheckInPoiView" owner:self options:nil] objectAtIndex:0];
    poiView->m_pInterop = pInterop;
    
    poiView->m_pController = [UIViewController alloc];
    [poiView->m_pController setView:poiView];
    poiView->m_stateChangeAnimationTimeSeconds = 0.2f;
    poiView.alpha = 0.f;
    poiView->m_boardingTimeLeft = 0;
    poiView->m_departureTimeLeft = 0;
    
    UINib *nib = [UINib nibWithNibName:@"GatePoiViewCell" bundle: [NSBundle mainBundle]];
    [poiView->m_pFlightTimingTableView registerNib:nib forCellReuseIdentifier:@"CellIdentifier"];
    
    return poiView;
    
}

- (void) layoutSubviews
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    
    float boundsOccupyMultiplierHeight;
    
    UIInterfaceOrientation currentOrientation = [UIApplication sharedApplication].statusBarOrientation;
    
    if(currentOrientation == UIInterfaceOrientationLandscapeLeft || currentOrientation == UIInterfaceOrientationLandscapeRight)
    {
        boundsOccupyMultiplierHeight = 0.755f;
    }
    else
    {
        boundsOccupyMultiplierHeight = 0.9f;
    }
    const float boundsOccupyMultiplierWidth = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth*boundsOccupyMultiplierWidth, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplierHeight;
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    
    float mainWindowY;
    
    if(currentOrientation == UIInterfaceOrientationLandscapeLeft || currentOrientation == UIInterfaceOrientationLandscapeRight)
    {
        mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.489f);
    }
    else
    {
        mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    }
    
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    
}

-(IBAction)HandleClosedButtonSelected:(id) sender
{
    m_pInterop->HandleCloseClicked();
    
}
- (IBAction)HandleShowMeWayButtonClick:(id)sender
{
    ExampleApp::Search::SdkModel::SearchResultModel model = m_pCurrentModel;
    m_pInterop->HandleCloseClicked();
    m_pInterop->HandleShowMeWayClicked(model);
}

-(void)dealloc
{
    [m_pBoardingTimeLabel release];
    [m_pDepartingLabel release];
    [m_pBoardingTimeCountDown release];
    [m_pContDownTimer invalidate];
    m_pContDownTimer = nil;
    //[m_pFlightTimingTableView release];
    [m_pController release];
    [m_pDepartingTimeCountDown release];
    [_pTitleLbl release];
    [super dealloc];


}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath      *)indexPath;
{
    return 25;
}
//UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return m_flightsVector.size()+1;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    EegeoSearchResultFlightTimingTableViewCell *cell = (EegeoSearchResultFlightTimingTableViewCell*)[tableView dequeueReusableCellWithIdentifier:@"CellIdentifier"];
    if (indexPath.row != 0)
    {
        cell.m_HeaderView.hidden = true;
        cell.m_DataView.hidden = false;
        
        ExampleApp::Search::SdkModel::FlightResultModel flightInfo  = m_flightsVector[indexPath.row-1];
        
        cell.m_pairLineName.text = [NSString stringWithUTF8String:flightInfo.GetAirLineName().c_str()];
        cell.m_pflightName.text = [NSString stringWithUTF8String:flightInfo.GetFlight().c_str()];
        cell.m_pdestination.text = [NSString stringWithUTF8String:flightInfo.GetFlightDestincation().c_str()];
        cell.m_pgateNum.text = [NSString stringWithUTF8String:flightInfo.GetGateNo().c_str()];
        cell.m_pflightTime.text = [NSString stringWithUTF8String:flightInfo.GetFlightTime().c_str()];
        
        if([cell.m_pgateNum.text isEqualToString:@"134"])
        {
            cell.backgroundColor = [UIColor colorWithRed:18/255.0 green:76/255.0 blue:167/255.0 alpha:1];
            UIColor *whiteColor = [UIColor whiteColor];
            cell.m_pairLineName.textColor = whiteColor;
            cell.m_pflightName.textColor = whiteColor;
            cell.m_pdestination.textColor = whiteColor;
            cell.m_pgateNum.textColor = whiteColor;
            cell.m_pflightTime.textColor = whiteColor;

        }
        else
        {
            cell.backgroundColor = [UIColor colorWithRed:243/255.0 green:246/255.0 blue:251/255.0 alpha:1];

        }

    }else
    {
        cell.m_DataView.hidden = true;
        cell.m_HeaderView.hidden = false;
        cell.backgroundColor = [UIColor colorWithRed:231/255.0 green:237/255.0 blue:246/255.0 alpha:1];

    }
    return cell;
}


@end
