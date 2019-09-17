if(${IOS})
set(headers ${headers} ios_src/SmsVerification
)
set(currsources
  ios_src/SmsVerification/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SmsVerification FILES ${currsources})
include(ios_src/SmsVerification/View/CMakeLists.txt)
include(ios_src/SmsVerification/SdkModel/CMakeLists.txt)
endif(${IOS})
