//
//  DirectionSuggestionTableViewCell.h
//  ExampleApp
//
//  Created by Qaiser Shehzad on 11/1/16.
//
//

#import <UIKit/UIKit.h>

@interface DirectionSuggestionTableViewCell : UITableViewCell
{
    
}
@property (retain, nonatomic) IBOutlet UILabel *titleLabel;
@property (retain, nonatomic) IBOutlet UILabel *subTitleLabel;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *titleLabelHeightConstraint;

@end
