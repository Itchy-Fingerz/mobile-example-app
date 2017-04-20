if(${IOS})
set(headers ${headers} ios_src/CustomAlert/View
)
set(currsources
  ios_src/CustomAlert/View/CMakeLists.txt
  ios_src/CustomAlert/View/ICustomAlertViewModule.h
  ios_src/CustomAlert/View/CustomAlertView.h
  ios_src/CustomAlert/View/CustomAlertView.mm
  ios_src/CustomAlert/View/CustomAlertViewIncludes.h
  ios_src/CustomAlert/View/CustomAlertViewInterop.h
  ios_src/CustomAlert/View/CustomAlertViewInterop.mm
  ios_src/CustomAlert/View/CustomAlertViewModule.h
  ios_src/CustomAlert/View/CustomAlertViewModule.mm
)
set(resources ${resources}
	ios_src/CustomAlert/View/CustomAlertView.xib
)

set(sources ${sources} ${currsources}
)
source_group(\\ios_src\\CustomAlert\\View FILES ${currsources})
endif(${IOS})
