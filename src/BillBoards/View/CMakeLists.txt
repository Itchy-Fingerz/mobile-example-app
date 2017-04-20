set(headers ${headers} ../src/BillBoards/View
)
set(currsources
  ../src/BillBoards/View/CMakeLists.txt
  ../src/BillBoards/View/BillBoardsModule.cpp
  ../src/BillBoards/View/BillBoardsModule.h
  ../src/BillBoards/View/BillBoardService.cpp
  ../src/BillBoards/View/BillBoardService.h
  ../src/BillBoards/View/GeometryHelpers.h
  ../src/BillBoards/View/GeometryHelpers.cpp
  ../src/BillBoards/View/BillBoardConfig.h
  ../src/BillBoards/View/BillBoardsMeshUnlitTexturedMaterial.h
  ../src/BillBoards/View/BillBoardsMeshUnlitTexturedMaterial.cpp
  ../src/BillBoards/View/BillBoardsMeshRenderable.h
  ../src/BillBoards/View/BillBoardsMeshRenderable.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\BillBoards\\View FILES ${currsources})
