set(headers ${headers} ../src/CustomAlert/View
)
set(currsources
  ../src/CustomAlert/View/CMakeLists.txt
  ../src/CustomAlert/View/ICustomAlertView.h
  ../src/CustomAlert/View/ICustomAlertViewModel.h
  ../src/CustomAlert/View/CustomAlertController.cpp
  ../src/CustomAlert/View/CustomAlertController.h
  ../src/CustomAlert/View/CustomAlertViewModel.cpp
  ../src/CustomAlert/View/CustomAlertViewModel.h
  ../src/CustomAlert/View/CustomAlertScreenControl.cpp
  ../src/CustomAlert/View/CustomAlertScreenControl.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\CustomAlert\\View FILES ${currsources})
