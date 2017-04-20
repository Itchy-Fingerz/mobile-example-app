// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

@interface EegeoSearchResultFlightTimingTableViewCell : UITableViewCell
{

}
@property (retain, nonatomic) IBOutlet UIView *m_HeaderView;
@property (retain, nonatomic) IBOutlet UIView *m_DataView;

@property (retain, nonatomic) IBOutlet UILabel *m_pairLineName;
@property (retain, nonatomic) IBOutlet UILabel *m_pflightName;
@property (retain, nonatomic) IBOutlet UILabel *m_pdestination;
@property (retain, nonatomic) IBOutlet UILabel *m_pgateNum;
@property (retain, nonatomic) IBOutlet UILabel *m_pflightTime;
@property (retain, nonatomic) IBOutlet UILabel *m_pDataViewprintStatuslbl;
@property (retain, nonatomic) IBOutlet UILabel *m_pPrintTimelbl;
@end
