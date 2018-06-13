if(${IOS})
set(headers ${headers} ios_src/SmsVerification/SdkModel
)
set(currsources
  ios_src/SmsVerification/SdkModel/CMakeLists.txt
)
set(resources ${resources}
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SmsVerification\\SdkModel FILES ${currsources})
include(ios_src/SmsVerification/SdkModel/LolayLocksmith/CMakeLists.txt)

endif(${IOS})
