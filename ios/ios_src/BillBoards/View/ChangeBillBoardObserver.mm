// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#import "ChangeBillBoardObserver.h"
#include "BillBoardsController.h"

@implementation ChangeBillBoardObserver

-(id)init:(ExampleApp::BillBoards::SdkModel::BillBoardsController*)billBoardController
{
    self = [super init];
    if (self)
    {
        [[NSNotificationCenter defaultCenter] addObserver: self
                                                 selector: @selector(onResume)
                                                     name: @"handleResume"
                                                   object: nil];
        m_pbillBoardController = billBoardController;
    }

    return self;
}
- (void)onResume
{
    m_pbillBoardController->RefreshBillBoards();
}
-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver: self
                                                    name: @"handleResume"
                                                  object: nil];
    [super dealloc];
}
@end
