set(headers ${headers} ../src/ThreeSixtyInteraction/View
)
set(currsources
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteraction.h
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteractionController.cpp
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteractionController.h
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteractionModule.cpp
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteractionModule.h
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewModel.cpp
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewModel.h
  ../src/ThreeSixtyInteraction/View/CMakeLists.txt
  ../src/ThreeSixtyInteraction/View/IThreeSixtyInteractionModule.h
  ../src/ThreeSixtyInteraction/View/IThreeSixtyInteractionView.h
  ../src/ThreeSixtyInteraction/View/IThreeSixtyInteractionViewModel.h
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteractionOpenableControl.h
  ../src/ThreeSixtyInteraction/View/ThreeSixtyInteractionOpenableControl.cpp

)
set(sources ${sources} ${currsources})
source_group(\\src\\ThreeSixtyInteraction\\View FILES ${currsources})
