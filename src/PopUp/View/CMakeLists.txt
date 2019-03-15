set(headers ${headers} ../src/PopUp/View
)
set(currsources
  ../src/PopUp/View/PopUp.h
  ../src/PopUp/View/PopUpController.cpp
  ../src/PopUp/View/PopUpController.h
  ../src/PopUp/View/PopUpModule.cpp
  ../src/PopUp/View/PopUpModule.h
  ../src/PopUp/View/PopUpViewModel.cpp
  ../src/PopUp/View/PopUpViewModel.h
  ../src/PopUp/View/CMakeLists.txt
  ../src/PopUp/View/IPopUpModule.h
  ../src/PopUp/View/IPopUpView.h
  ../src/PopUp/View/IPopUpViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\PopUp\\View FILES ${currsources})
