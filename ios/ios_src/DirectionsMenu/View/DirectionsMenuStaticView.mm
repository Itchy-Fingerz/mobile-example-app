// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuStaticView.h"
#include "DirectionsMenuWayPointViewCell.h"
#include "MenuSectionViewModel.h"
#include "DirectionsMenuView.h"
#include "DirectionsMenuViewInterop.h"
#include "UIColors.h"
#include "DirectionSuggestionTableViewCell.h"
#include "LatLongAltitude.h"
#include "SearchResultItemModel.h"

@interface DirectionsMenuStaticView()
{
    ExampleApp::Menu::View::IMenuSectionViewModel* m_pSearchResultsSection;
    
    std::vector< ExampleApp::Search::SdkModel::SearchResultModel> m_pSuggestionsResults;
    std::vector< ExampleApp::Search::SdkModel::SearchResultModel> m_internalPoiSuggestions;

    ExampleApp::Search::SdkModel::SearchResultModel m_pStartLoc;
    ExampleApp::Search::SdkModel::SearchResultModel m_pEndLoc;
    
    UIView *m_pView;
    int selectedIndex;
    int searchType;
    BOOL startLocationSearched;
    BOOL endLocationSearched;
    BOOL startMyLocationSelected;
}

@property (retain, nonatomic) IBOutlet UIView *startRouteBgView;
@property (retain, nonatomic) IBOutlet UIView *endRouteBgView;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *contentHeightConstraint;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *endHeightConstraint;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *startContainerHeightConstraint;
@property (retain, nonatomic) IBOutlet UITableView *wayPointsTableView;

@property (retain, nonatomic) IBOutlet NSLayoutConstraint *heightConstraintForMyLocationView;

@property (retain, nonatomic) IBOutlet NSLayoutConstraint *heightDropSpacingConstraint;
@property (retain, nonatomic) IBOutlet UIView *suggestionsView;
@property (retain, nonatomic) IBOutlet UILabel *minCounterLabel;
@property (retain, nonatomic) IBOutlet UILabel *secCounterLabel;
@property (retain, nonatomic) IBOutlet UILabel *staticMinsLabel;

@property (retain, nonatomic) IBOutlet UITableView *suggestionsTableView;
@end

@implementation DirectionsMenuStaticView

- (void)awakeFromNib
{
    [super awakeFromNib];
    m_pSearchResultsSection = NULL;
    //Changes done directly here, we have an object
    [_reverseButton.layer setBorderWidth:1.0f];
    [_reverseButton.layer setBorderColor:[UIColor whiteColor].CGColor];
    _reverseButton.layer.cornerRadius = 3.0f;
    
    _startRouteBgView.layer.cornerRadius = 3.0f;
    _endRouteBgView.layer.cornerRadius = 3.0f;
    
    _wayPointsTableView.delegate = self;
    _wayPointsTableView.dataSource = self;
    
    _suggestionsTableView.delegate = self;
    _suggestionsTableView.dataSource = self;
    
    selectedIndex = -1;
    searchType = -1;
    startMyLocationSelected = true;
    
    UINib *wayPointsCellNib = [UINib nibWithNibName:@"DirectionsMenuWayPointViewCell" bundle: [NSBundle mainBundle]];
    [self.wayPointsTableView registerNib:wayPointsCellNib forCellReuseIdentifier:@"DirectionsMenuWayPointViewCell"];

    
    UINib *suggestionCellNib = [UINib nibWithNibName:@"DirectionSuggestionsViewCell" bundle: [NSBundle mainBundle]];
    [self.suggestionsTableView registerNib:suggestionCellNib forCellReuseIdentifier:@"DirectionSuggestionsViewCell"];
    
    [_startRouteTextField setText:@"My Location"];
    
    [self.minCounterLabel setHidden:YES];
    [self.secCounterLabel setHidden:YES];
    [self.staticMinsLabel setHidden:YES];

}


- (void) layoutSubviews
{
    [super layoutSubviews];
}
- (IBAction)cancelSuggestions:(id)sender
{
    _heightDropSpacingConstraint.constant = 0;
    _suggestionsView.hidden = true;
    searchType = -1;
    [self layoutIfNeeded];
    
    
}
- (void)showStartSuggestions
{
    startLocationSearched = false;
    [_spinner startAnimating];
    _heightDropSpacingConstraint.constant = 0;
    _suggestionsView.hidden = false;
    searchType = 1;
    _myLocation.hidden = false;
    _heightConstraintForMyLocationView.constant = 45;
    [self layoutIfNeeded];
}
- (void)showEndSuggestions
{
    endLocationSearched = false;
    [_spinner startAnimating];
    _heightDropSpacingConstraint.constant = 55;
    _suggestionsView.hidden = false;
    searchType = 2;
    _myLocation.hidden = true;
    _heightConstraintForMyLocationView.constant = 2;
    [self layoutIfNeeded];
}
- (void)reverseAction
{
    ExampleApp::Search::SdkModel::SearchResultModel temp = m_pStartLoc;
    m_pStartLoc = m_pEndLoc;
    m_pEndLoc = temp;

    NSString *temptextStart = _startRouteTextField.text;
    _startRouteTextField.text = _endRouteTextField.text;
    _endRouteTextField.text = temptextStart;
    
    bool tempSearched = endLocationSearched;
    endLocationSearched = startLocationSearched;
    startLocationSearched = tempSearched;
    
    selectedIndex = -1;
    
}
- (void)searchProgress:(bool)inProgress
{
    if (inProgress)
    {
        [_waypointspinner startAnimating];
    }
    else
    {
        [_waypointspinner stopAnimating];
    }
    
}
- (void)optionsAction
{
 
    if(_optionsButton.isSelected)
    {
        [_optionsButton setSelected:NO];
        
        [_endHeightConstraint setConstant:115.0f];
        [_startContainerHeightConstraint setConstant:55.0f];
        [UIView animateWithDuration:0.5
                     animations:^{
                         [self layoutIfNeeded];
                     }];
    }
    else
    {
        [_optionsButton setSelected:YES];
        [_endHeightConstraint setConstant:64.0f];
        [_startContainerHeightConstraint setConstant:0.f];
        [UIView animateWithDuration:0.5
                         animations:^{
                             [self layoutIfNeeded];
                         }];
    }
    
    
}

- (void)updateSearchResultsSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)section  {
    
    selectedIndex = -1;

     m_pSearchResultsSection = section;
    
    if (section == NULL)
    {
        [_waypointspinner startAnimating];
    }
    else
    {
        [_waypointspinner stopAnimating];
    }
    
    [self UpdateRouteTime];
    
    [_wayPointsTableView reloadData];
    

}
- (void)updateStartSuggestions:(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>&) results isForGeoNames:(bool)geoName
{
    if (geoName)
    {
        m_pSuggestionsResults = results;
    }
    else
    {
        m_internalPoiSuggestions = results;
        
    }
//    startLocationSearched = false;
//    if (m_pSuggestionsResults.size() > 0 || m_internalPoiSuggestions.size() > 0)
//    {
//        [self showStartSuggestions];
//    }
    [_spinner stopAnimating];
    [_suggestionsTableView reloadData];
    
}

- (void)updateEndSuggestions:(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>&) results isForGeoNames:(bool)geoName
{
    if (geoName)
    {
        m_pSuggestionsResults = results;
    }
    else
    {
        m_internalPoiSuggestions = results;
        
    }
//    endLocationSearched = false;
    
//    if (m_pSuggestionsResults.size() > 0 || m_internalPoiSuggestions.size() > 0)
//    {
//        [self showEndSuggestions];
//    }
    [_spinner stopAnimating];
    [_suggestionsTableView reloadData];
    
}
#define  UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    if(tableView == _suggestionsTableView)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    
    if (tableView == _suggestionsTableView)
    {
        if(section == 0)
        {
            return m_internalPoiSuggestions.size();
        }
        else
        {
            return m_pSuggestionsResults.size();
        }
        
        
    }
    if(m_pSearchResultsSection == NULL)
    {
        return 0;
    }
    else
    {
        return m_pSearchResultsSection->Size();        
    }
}

- (UIView *) tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    return [[[UIView alloc] initWithFrame:CGRectMake(0, 0, tableView.bounds.size.width, 0)] autorelease];
}

-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 0;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (tableView == _suggestionsTableView) {
        
        ExampleApp::Search::SdkModel::SearchResultModel item;
        if(indexPath.section == 0)
        {
            item = m_internalPoiSuggestions[(static_cast<int>(indexPath.row))];
        }
        else
        {
            item = m_pSuggestionsResults[(static_cast<int>(indexPath.row))];
        }
        
        DirectionSuggestionTableViewCell *cell = (DirectionSuggestionTableViewCell*)[self.suggestionsTableView dequeueReusableCellWithIdentifier:@"DirectionSuggestionsViewCell"];
        
        [cell.titleLabel setText:[NSString stringWithFormat:@"%s",item.GetTitle().c_str()]];

        return cell;
        
    }
    
    
    DirectionsMenuWayPointViewCell *cell = (DirectionsMenuWayPointViewCell*)[self.wayPointsTableView dequeueReusableCellWithIdentifier:@"DirectionsMenuWayPointViewCell"];
    
    if(indexPath.row < m_pSearchResultsSection->Size())
    {
        ExampleApp::Menu::View::MenuItemModel item = m_pSearchResultsSection->GetItemAtIndex(static_cast<int>(indexPath.row));
 
        ExampleApp::SearchResultSection::View::SearchResultItemModel &searchItem = (ExampleApp::SearchResultSection::View::SearchResultItemModel&)item.MenuOption();
        



        if(searchItem.GetWayPointType() == ExampleApp::PathDrawing::WayPointType::Left || searchItem.GetWayPointType() == ExampleApp::PathDrawing::WayPointType::Right)
        {
            int wayPointNumber = searchItem.GetWayPointNumber();
            [cell.wayPointNumberlbl setText:[NSString stringWithFormat:@"%i",wayPointNumber]];
            cell.wayPointNumberlbl.hidden = false;
            cell.m_pWaypointNumberLabelBG.hidden = false;
        }
        else
        {
            cell.wayPointNumberlbl.hidden = true;
            cell.m_pWaypointNumberLabelBG.hidden = true;
        }

        
        std::string json = item.SerializeJson();
        
        rapidjson::Document document;
        
        
        if (!document.Parse<0>(json.c_str()).HasParseError())
        {
            std::string title = document.HasMember("name") ? document["name"].GetString() : "";
            std::string stitle = searchItem.GetName();
            if (title == "unknown")
            {
                title = "Unknown location";
            }
            
            std::string subTitle = document.HasMember("details") ? document["details"].GetString() : "";
            
            std::string icon = document.HasMember("icon") ? document["icon"].GetString() : "misc";
            
            std::string duration = document.HasMember("duration") ? document["duration"].GetString() : "";
            
            [cell.wayPointImageView setImage:[UIImage imageNamed:[NSString stringWithCString:icon.c_str() encoding:NSUTF8StringEncoding]]];
            if(indexPath.row == 0)
            {
                [cell.wayPointMainTitlelbl setText:_startRouteTextField.text];
                cell.wayPointSubCategorylbl.hidden = true;

            }
            else if (indexPath.row == m_pSearchResultsSection->Size() - 1)
            {
                [cell.wayPointMainTitlelbl setText:_endRouteTextField.text];
                cell.wayPointSubCategorylbl.hidden = true;
            }
            else
            {
                [cell.wayPointMainTitlelbl setText:[NSString stringWithCString:title.c_str() encoding:NSUTF8StringEncoding]];
                cell.wayPointSubCategorylbl.hidden = false;
            }
            
            NSString * pSubtitle = [NSString stringWithCString:stitle.c_str() encoding:NSUTF8StringEncoding];
            if ([pSubtitle rangeOfString:@"straight"].location != NSNotFound)
            {
                pSubtitle = [NSString stringWithFormat:@"Then %@",pSubtitle];
            }
            else if ([pSubtitle rangeOfString:@"right"].location != NSNotFound)
            {
                pSubtitle = [NSString stringWithFormat:@"Turn %@",pSubtitle];

            }
            else if ([pSubtitle rangeOfString:@"left"].location != NSNotFound)
            {
                pSubtitle = [NSString stringWithFormat:@"Turn %@",pSubtitle];

            }
            else
            {
                pSubtitle = [pSubtitle capitalizedString];
            }
            
            NSArray *pSubTitleArray = [pSubtitle componentsSeparatedByString: @" "];
            
            if ([pSubTitleArray count] >= 2)
            {
                NSString *pDistanceString = [pSubTitleArray lastObject];
                
                NSRange range1 = [pSubtitle rangeOfString:pDistanceString];
                
                NSMutableAttributedString *attributedText = [[NSMutableAttributedString alloc] initWithString:pSubtitle];
                
                [attributedText setAttributes:@{NSFontAttributeName:[UIFont boldSystemFontOfSize:cell.wayPointSubCategorylbl.font.pointSize]}
                                        range:range1];
                
                
                
                [cell.wayPointSubCategorylbl setAttributedText:attributedText];
            }
            else
            {
                [cell.wayPointSubCategorylbl setText:pSubtitle];

            }


        }
        UIView *pView = [[UIView alloc]init];
        pView.backgroundColor = [UIColor colorWithRed:234.0f/255.0f green:251.0f/255.0f blue:167.0f/255.0f alpha:1.0f];
        cell.selectedBackgroundView = pView;
        if(indexPath.row == selectedIndex)
        {
            [cell.mainContainerView setBackgroundColor:[UIColor colorWithRed:234.0f/255.0f green:251.0f/255.0f blue:167.0f/255.0f alpha:1.0f]];
            [cell.wayPointMainTitlelbl setTextColor:[UIColor blackColor]];
            [cell.wayPointSubCategorylbl setTextColor:[UIColor colorWithRed:163.0f/255.0f green:163.0f/255.0f blue:163.0f/255.0f alpha:1.0f]];
            
        }
        else if(searchItem.GetWayPointType() == ExampleApp::PathDrawing::WayPointType::Elevator)
        {
            [cell.mainContainerView setBackgroundColor:[UIColor colorWithRed:16.0f/255.0f green:64.0f/255.0f blue:160.0f/255.0f alpha:1.0f]];
            [cell.wayPointMainTitlelbl setTextColor:[UIColor whiteColor]];
            [cell.wayPointSubCategorylbl setTextColor:[UIColor whiteColor]];
        
        }
        else
        {
            [cell.mainContainerView setBackgroundColor:[UIColor colorWithRed:248.0f/255.0f green:248.0f/255.0f blue:248.0f/255.0f alpha:1.0f]];
            [cell.wayPointMainTitlelbl setTextColor:[UIColor blackColor]];
            [cell.wayPointSubCategorylbl setTextColor:[UIColor colorWithRed:163.0f/255.0f green:163.0f/255.0f blue:163.0f/255.0f alpha:1.0f]];
            
        }
        
    }

    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return 45;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    if (tableView == _suggestionsTableView) {
    
        ExampleApp::Search::SdkModel::SearchResultModel item;
        if(indexPath.section == 0)
        {
            item = m_internalPoiSuggestions[(static_cast<int>(indexPath.row))];
        }
        else
        {
            item = m_pSuggestionsResults[(static_cast<int>(indexPath.row))];
        }
        
        if(searchType == 1 ) //start
        {
            m_pStartLoc = item;
            startLocationSearched = true;
            [_startRouteTextField setText:[NSString stringWithFormat:@"%s",item.GetTitle().c_str()]];
            [_endRouteTextField becomeFirstResponder];
        }
        
        if(searchType == 2) //end
        {
            m_pEndLoc = item;
            endLocationSearched = true;
            [_endRouteTextField setText:[NSString stringWithFormat:@"%s",item.GetTitle().c_str()]];
        }
        [self cancelSuggestions:nil];

        return;
    }
    DirectionsMenuView *parentView = (DirectionsMenuView *)m_pView;
    ExampleApp::DirectionsMenu::View::DirectionsMenuViewInterop *interop = [parentView getDirectionsMenuInterop];
    interop->HandleWayPointSelected(static_cast<int>(indexPath.row));
    
}

-(void)UpdateRouteTime  {
    
    
    [self.minCounterLabel setHidden:YES];
    [self.secCounterLabel setHidden:YES];
    [self.staticMinsLabel setHidden:YES];
    
    if(m_pSearchResultsSection != NULL &&  m_pSearchResultsSection->Size() > 0)
    {
        int duration_sec = 0;

        for (int i= 0; i<m_pSearchResultsSection->Size(); i++)
        {
            ExampleApp::Menu::View::MenuItemModel item = m_pSearchResultsSection->GetItemAtIndex(static_cast<int>(i));
            
            std::string json = item.SerializeJson();
            
            rapidjson::Document document;
            
            
            if (!document.Parse<0>(json.c_str()).HasParseError())
            {
                std::string subTitle = document.HasMember("details") ? document["details"].GetString() : "";
                duration_sec += std::stoi( subTitle );
            }
        
        }
        
        int mins = duration_sec / 60;
        int sec = duration_sec % 60;
        [self.minCounterLabel setText:[NSString stringWithFormat:@"%i",mins]];
        [self.secCounterLabel setText:[NSString stringWithFormat:@"%isec",sec]];
        
        [self.minCounterLabel setHidden:NO];
        [self.secCounterLabel setHidden:NO];
        [self.staticMinsLabel setHidden:NO];

    }
}

- (Eegeo::Space::LatLong) GetStartLocation
{
    if ((startMyLocationSelected && [_startRouteTextField.text isEqualToString:@"My Location"])) {
        return Eegeo::Space::LatLong(0.0f,0.0f);
    }
    if (startLocationSearched)
    {
      return m_pStartLoc.GetLocation();
    }
    return Eegeo::Space::LatLong(0.0f,0.0f);
    
}
- (int)GetStartLevel
{
    if ((startMyLocationSelected && [_startRouteTextField.text isEqualToString:@"My Location"])) {
        return -1;
    }
    if (startLocationSearched)
    {
        return m_pStartLoc.GetFloor();
    }
    return -1;
}

- (Eegeo::Space::LatLong) GetEndLocation
{
    if (([_endRouteTextField.text isEqualToString:@"My Location"])) {
        return Eegeo::Space::LatLong(0.0f,0.0f);
    }
    if (endLocationSearched)
    {
        return m_pEndLoc.GetLocation();
    }
    return Eegeo::Space::LatLong(0.0f,0.0f);

}

- (int)GetEndLevel
{
    if (([_endRouteTextField.text isEqualToString:@"My Location"])) {
        return -1;
    }
    if (endLocationSearched)
    {
        return m_pEndLoc.GetFloor();
    }
    return -1;
}

-(std::string) GetStartBuildinID
{
    if (([_startRouteTextField.text isEqualToString:@"My Location"])) {
        return "";
    }
    if (startLocationSearched)
    {
        return m_pStartLoc.GetBuildingId().Value();
    }
    return "";
}

-(std::string) GetEndBuildinID
{
    if (([_endRouteTextField.text isEqualToString:@"My Location"])) {
        return "";
    }
    if (endLocationSearched)
    {
        return m_pEndLoc.GetBuildingId().Value();
    }
    return "";
}

- (void) resetSuggestionItem
{
    startLocationSearched = false;
    endLocationSearched = false;
    startMyLocationSelected = true;
    selectedIndex = -1;
    [_wayPointsTableView reloadData];
}
- (BOOL) shouldPerformSearch
{
    
    Eegeo::Space::LatLong startLatLong = Eegeo::Space::LatLong::FromDegrees(m_pStartLoc.GetLocation().GetLatitudeInDegrees(), m_pStartLoc.GetLocation().GetLongitudeInDegrees());
    Eegeo::Space::LatLong endLatLong = Eegeo::Space::LatLong::FromDegrees(m_pEndLoc.GetLocation().GetLatitudeInDegrees(), m_pEndLoc.GetLocation().GetLongitudeInDegrees());
    
    if (startLatLong.GetLongitudeInDegrees() == 0 && startLatLong.GetLongitudeInDegrees() == 0 && endLatLong.GetLongitudeInDegrees() == 0 && endLatLong.GetLongitudeInDegrees() == 0)
    {
        return false;
    }
    
    if ((startLocationSearched || (startMyLocationSelected && [_startRouteTextField.text isEqualToString:@"My Location"])) && (endLocationSearched || ([_endRouteTextField.text isEqualToString:@"My Location"] && startLocationSearched)))
    {
        return true;
    }
    return false;
}
-(void)SetSearchMenuView:(UIView *)_parentView   {
    
    m_pView = _parentView;
}

- (IBAction)MyLocationSelected:(id)sender {
    
    startMyLocationSelected = true;
    [_startRouteTextField setText:@"My Location"];
    [self cancelSuggestions:nil];
    [_endRouteTextField becomeFirstResponder];
    
}

-(void)SetHighlightItem:(int)highlightItem  {
    
    selectedIndex = highlightItem;
    [_wayPointsTableView reloadData];
}

-(float)getEstimatedHeight {

    float estimatedHeight = 300;  //default value
    if(m_pSearchResultsSection == NULL || m_pSearchResultsSection->Size() == 0)
    {
        if (searchType  == 1)
        {
            estimatedHeight = _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (_hideOptionsView.bounds.size.height) + 150;
            //return
        }
        else if (searchType  == 2)
        {
            estimatedHeight = _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (_hideOptionsView.bounds.size.height) + 175;
            //return
        }
        else
        {
            estimatedHeight = _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (_hideOptionsView.bounds.size.height)+_endHeightConstraint.constant;
        }
        

    }
    else
    {
        estimatedHeight = _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (45  * m_pSearchResultsSection->Size()) + (_hideOptionsView.bounds.size.height)+_endHeightConstraint.constant +_startContainerHeightConstraint.constant;
    }
    CGRect screenBounds = [[UIScreen mainScreen] bounds];

    if (estimatedHeight > (screenBounds.size.height - 175) ) {
        return (screenBounds.size.height - 175);
    }
    return estimatedHeight;
}

- (void)dealloc {
    
    [_contentHeightConstraint release];
    [_endHeightConstraint release];
    [_optionsButton release];
    [_exitDirectionsBtn release];
    [_endRouteTextField release];
    [_startRouteTextField release];\
    
    [_startContainerHeightConstraint release];
    [_heightDropSpacingConstraint release];
    [_suggestionsView release];
    [_suggestionsTableView release];
    [_myLocation release];
    [_minCounterLabel release];
    [_secCounterLabel release];
    [_staticMinsLabel release];
    [_spinner release];
    [_waypointspinner release];
    [_heightConstraintForMyLocationView release];
    [super dealloc];
}

@end
