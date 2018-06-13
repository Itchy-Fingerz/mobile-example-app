if(${IOS})
set(headers ${headers} ios_src/SmsVerification/SdkModel/LolayLocksmith
)
set(currsources
  ios_src/SmsVerification/SdkModel/LolayLocksmith/CMakeLists.txt
  ios_src/SmsVerification/SdkModel/LolayLocksmith/LolayKeychain.h
  ios_src/SmsVerification/SdkModel/LolayLocksmith/LolayKeychain.m
  ios_src/SmsVerification/SdkModel/LolayLocksmith/LolayLocksmithGlobals.h  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSData+LolayBase64.h  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSData+LolayBase64.m  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSData+LolayHmacSha1.h  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSData+LolayHmacSha1.m  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSData+LolaySha512.h  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSData+LolaySha512.m  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSString+LolayBase64.h  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSString+LolayBase64.m  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSUserDefaults+LolayBase64.h  ios_src/SmsVerification/SdkModel/LolayLocksmith/NSUserDefaults+LolayBase64.m
)
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-w")
set(resources ${resources}
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SmsVerification\\SdkModel\\LolayLocksmith FILES ${currsources})
endif(${IOS})
