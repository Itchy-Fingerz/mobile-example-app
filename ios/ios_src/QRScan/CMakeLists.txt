if(${IOS})
set(headers ${headers} ios_src/AboutPage
)
set(currsources
  ios_src/QRScan/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\QRScan FILES ${currsources})
include(ios_src/QRScan/View/CMakeLists.txt)
endif(${IOS})
