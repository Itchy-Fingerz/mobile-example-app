// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "BillBoardsController.h"

@interface ChangeBillBoardObserver : NSObject
{
    ExampleApp::BillBoards::SdkModel::BillBoardsController* m_pbillBoardController;
}
-(id)init:(ExampleApp::BillBoards::SdkModel::BillBoardsController*)billBoardController;

@end

