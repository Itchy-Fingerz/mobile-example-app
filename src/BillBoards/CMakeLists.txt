set(headers ${headers} ../src/BillBoards
)
set(currsources
  ../src/BillBoards/BillBoards.h
  ../src/BillBoards/BillBoardSelectedMessage.h
  ../src/BillBoards/ShowOfferHighlightMessage
  ../src/BillBoards/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\BillBoards FILES ${currsources})
include(../src/BillBoards/SdkModel/CMakeLists.txt)
include(../src/BillBoards/View/CMakeLists.txt)
