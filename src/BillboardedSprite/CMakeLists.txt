set(headers ${headers} ../src/BillboardedSprite
)
set(currsources
  ../src/BillboardedSprite/BillboardedSpriteExample.cpp
  ../src/BillboardedSprite/BillboardedSpriteExample.h
  ../src/BillboardedSprite/CMakeLists.txt

)
set(sources ${sources} ${currsources})
source_group(\\src\\BillboardedSprite FILES ${currsources})
