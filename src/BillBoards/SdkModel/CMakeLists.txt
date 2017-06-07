set(headers ${headers} ../src/BillBoards/SdkModel
)
set(currsources
  ../src/BillBoards/SdkModel/CMakeLists.txt
  ../src/BillBoards/SdkModel/BillBoardsController.cpp
  ../src/BillBoards/SdkModel/BillBoardsController.h
  ../src/BillBoards/SdkModel/BillBoardModel.cpp
  ../src/BillBoards/SdkModel/BillBoardModel.h
  ../src/BillBoards/SdkModel/BillBoardsRepository.cpp
  ../src/BillBoards/SdkModel/BillBoardsRepository.h
  ../src/BillBoards/SdkModel/BillBoardInteriorStateChangedObserver.h
  ../src/BillBoards/SdkModel/BillBoardInteriorStateChangedObserver.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\BillBoards\\SdkModel FILES ${currsources})
