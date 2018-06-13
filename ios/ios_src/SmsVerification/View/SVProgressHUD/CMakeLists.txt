if(${IOS})
set(headers ${headers} ios_src/SmsVerification/View/SVProgressHUD
)
set(currsources

  ios_src/SmsVerification/View/SVProgressHUD/CMakeLists.txt  ios_src/SmsVerification/View/SVProgressHUD/SVIndefiniteAnimatedView.h  ios_src/SmsVerification/View/SVProgressHUD/SVIndefiniteAnimatedView.m  ios_src/SmsVerification/View/SVProgressHUD/SVProgressAnimatedView.h  ios_src/SmsVerification/View/SVProgressHUD/SVProgressAnimatedView.m  ios_src/SmsVerification/View/SVProgressHUD/SVProgressHUD-Prefix.pch  ios_src/SmsVerification/View/SVProgressHUD/SVProgressHUD.bundle  ios_src/SmsVerification/View/SVProgressHUD/SVProgressHUD.h  ios_src/SmsVerification/View/SVProgressHUD/SVProgressHUD.m  ios_src/SmsVerification/View/SVProgressHUD/SVRadialGradientLayer.h  ios_src/SmsVerification/View/SVProgressHUD/SVRadialGradientLayer.m
)
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc")
set(resources ${resources}
ios_src/SmsVerification/View/SVProgressHUD/SVProgressHUD.bundle
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SmsVerification\\View\\SVProgressHUD FILES ${currsources})
endif(${IOS})
