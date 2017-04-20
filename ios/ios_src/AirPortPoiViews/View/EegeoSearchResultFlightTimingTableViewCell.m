// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "EegeoSearchResultFlightTimingTableViewCell.h"

@implementation EegeoSearchResultFlightTimingTableViewCell

- (void)awakeFromNib
{
    [super awakeFromNib];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
}

- (void)dealloc {
    [_m_pairLineName release];
    [_m_pflightName release];
    [_m_pdestination release];
    [_m_pgateNum release];
    [_m_pflightTime release];
    [super dealloc];
}
@end
