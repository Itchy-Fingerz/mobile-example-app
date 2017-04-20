if(${IOS})
set(headers ${headers} ios_src/BillBoards
)
set(currsources
  ios_src/BillBoards/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Compass FILES ${currsources})
include(ios_src/BillBoards/View/CMakeLists.txt)
endif(${IOS})