if(${IOS})
set(headers ${headers} ios_src/SmsVerification/View/MZTimerLabel
)
set(currsources
  ios_src/SmsVerification/View/MZTimerLabel/CMakeLists.txt
  ios_src/SmsVerification/View/MZTimerLabel/MZTimerLabel.h
  ios_src/SmsVerification/View/MZTimerLabel/MZTimerLabel.m
)
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc")
set(resources ${resources}
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SmsVerification\\View\\MZTimerLabel FILES ${currsources})
endif(${IOS})
