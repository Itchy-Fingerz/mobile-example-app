set(headers ${headers} ../src/CustomAlert
)
set(currsources
  ../src/CustomAlert/CMakeLists.txt
  ../src/CustomAlert/SetCustomAlertVisibilityMessage.h
  ../src/CustomAlert/CustomAlert.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\CustomAlert FILES ${currsources})
include(../src/CustomAlert/SdkModel/CMakeLists.txt)
include(../src/CustomAlert/View/CMakeLists.txt)
