if(${IOS})
set(headers ${headers} ios_src/PopUp/View
)
set(currsources
  ios_src/PopUp/View/PopUpView.h
  ios_src/PopUp/View/PopUpView.mm
  ios_src/PopUp/View/PopUpViewIncludes.h
  ios_src/PopUp/View/PopUpViewModule.h
  ios_src/PopUp/View/PopUpViewModule.mm
  ios_src/PopUp/View/PopUpViewInterop.h
  ios_src/PopUp/View/PopUpViewInterop.mm
  ios_src/PopUp/View/CMakeLists.txt
  ios_src/PopUp/View/IPopUpViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\PopUp\\View FILES ${currsources})
endif(${IOS})
