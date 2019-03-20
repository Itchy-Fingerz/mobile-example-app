set(headers ${headers} ../src/ARMode/SdkModel
)
set(currsources
  ../src/ARMode/SdkModel/ARModeMenuModule.cpp
  ../src/ARMode/SdkModel/IARModeMenuModule.h
  ../src/ARMode/SdkModel/ARModeMenuModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ARMode\\SdkModel FILES ${currsources})
