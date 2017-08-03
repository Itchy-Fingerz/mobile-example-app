if(${IOS})
set(headers ${headers} ios_src/BillBoards/View
)
set(currsources
  ios_src/BillBoards/View/CMakeLists.txt
  ios_src/BillBoards/View/BillBoardsViewModule.cpp
  ios_src/BillBoards/View/BillBoardsViewModule.h
  ios_src/BillBoards/View/BillBoardsIncludes.h

)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\BillBoards\\View FILES ${currsources})
endif(${IOS})
