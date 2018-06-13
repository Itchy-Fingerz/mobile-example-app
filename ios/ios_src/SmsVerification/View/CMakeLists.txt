if(${IOS})
set(headers ${headers} ios_src/SmsVerification/View
)
set(currsources
  ios_src/SmsVerification/View/CMakeLists.txt
  ios_src/SmsVerification/View/ShowErrorMessageViewController.h
  ios_src/SmsVerification/View/ShowErrorMessageViewController.mm
  ios_src/SmsVerification/View/InputPhoneNumberViewController.h
  ios_src/SmsVerification/View/InputPhoneNumberViewController.mm
  ios_src/SmsVerification/View/InputValidationCodeViewController.h
  ios_src/SmsVerification/View/InputValidationCodeViewController.mm
  ios_src/SmsVerification/View/ValidationSucessViewController.h
  ios_src/SmsVerification/View/ValidationSucessViewController.mm
  ios_src/SmsVerification/View/SmsValidationBaseViewController.h
  ios_src/SmsVerification/View/SmsValidationBaseViewController.mm
)
set(resources ${resources}
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SmsVerification\\View FILES ${currsources})
include(ios_src/SmsVerification/View/MZTimerLabel/CMakeLists.txt)
include(ios_src/SmsVerification/View/SVProgressHUD/CMakeLists.txt)
endif(${IOS})
