set(headers ${headers} ../src/VenueLabels
)
set(currsources
  ../src/VenueLabels/CMakeLists.txt
  ../src/VenueLabels/VenueLabels.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\VenueLabels FILES ${currsources})
include(../src/VenueLabels/SdkModel/CMakeLists.txt)
