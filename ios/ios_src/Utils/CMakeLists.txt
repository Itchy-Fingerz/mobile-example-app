if(${IOS})
set(headers ${headers} ios_src/Utils
)
set(currsources
  ios_src/Utils/IosUtils.h
  ios_src/Utils/IosUtils.mm
  ios_src/Utils/CMakeLists.txt

)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Utils FILES ${currsources})
endif(${IOS})
