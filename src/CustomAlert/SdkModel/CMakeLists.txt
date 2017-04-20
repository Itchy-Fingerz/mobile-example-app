set(headers ${headers} ../src/CustomAlert/SdkModel
)
set(currsources
  ../src/CustomAlert/SdkModel/CMakeLists.txt
  ../src/CustomAlert/SdkModel/ICustomAlertModule.h
  ../src/CustomAlert/SdkModel/CustomAlertInteriorStateChangedObserver.cpp
  ../src/CustomAlert/SdkModel/CustomAlertInteriorStateChangedObserver.h
  ../src/CustomAlert/SdkModel/CustomAlertModule.cpp
  ../src/CustomAlert/SdkModel/CustomAlertModule.h
  ../src/CustomAlert/SdkModel/CustomAlertModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\CustomAlert\\SdkModel FILES ${currsources})
