if(${IOS})
set(headers ${headers} ios_src/ThreeSixtyInteraction/View
)
set(currsources
  ios_src/ThreeSixtyInteraction/View/ThreeSixtyInteractionView.h
  ios_src/ThreeSixtyInteraction/View/ThreeSixtyInteractionView.mm
  ios_src/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewIncludes.h
  ios_src/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewInterop.h
  ios_src/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewInterop.mm
  ios_src/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewModule.h
  ios_src/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewModule.mm
  ios_src/ThreeSixtyInteraction/View/CMakeLists.txt
  ios_src/ThreeSixtyInteraction/View/IThreeSixtyInteractionViewModule.h
)
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-w")
set(sources ${sources} ${currsources})
source_group(\\ios_src\\ThreeSixtyInteraction\\View FILES ${currsources})
endif(${IOS})
