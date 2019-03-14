set(headers ${headers} ../src/InteractionModelStateChangedObserver
)
set(currsources
  ../src/InteractionModelStateChangedObserver/InteractionModelStateChangedObserver.cpp
  ../src/InteractionModelStateChangedObserver/InteractionModelStateChangedObserver.h
  ../src/InteractionModelStateChangedObserver/CMakeLists.txt

)
set(sources ${sources} ${currsources})
source_group(\\src\\InteractionModelStateChangedObserver FILES ${currsources})
