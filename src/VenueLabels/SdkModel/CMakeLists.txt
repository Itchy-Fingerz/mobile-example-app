set(headers ${headers} ../src/VenueLabels/SdkModel
)
set(currsources
  ../src/VenueLabels/SdkModel/CMakeLists.txt
  ../src/VenueLabels/SdkModel/IVenueLabelsModule.h
  ../src/VenueLabels/SdkModel/IVenueLabelsController.h
  ../src/VenueLabels/SdkModel/VenueLabelsModule.cpp
  ../src/VenueLabels/SdkModel/VenueLabelsModule.h
  ../src/VenueLabels/SdkModel/VenueLabelsController.cpp
  ../src/VenueLabels/SdkModel/VenueLabelsController.h
  ../src/VenueLabels/SdkModel/VenueLabelsChangedObserver.cpp
  ../src/VenueLabels/SdkModel/VenueLabelsChangedObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\VenueLabels\\SdkModel FILES ${currsources})
