set(headers ${headers} ../src/AnimatedModels/SdkModel
)
set(currsources
  ../src/AnimatedModels/SdkModel/AnimatedModel.cpp
  ../src/AnimatedModels/SdkModel/AnimatedModel.h
  ../src/AnimatedModels/SdkModel/AnimatedModelsController.cpp
  ../src/AnimatedModels/SdkModel/AnimatedModelsController.h
  ../src/AnimatedModels/SdkModel/AnimatedModelsFactory.cpp
  ../src/AnimatedModels/SdkModel/AnimatedModelsFactory.h
  ../src/AnimatedModels/SdkModel/AnimatedModelsModule.cpp
  ../src/AnimatedModels/SdkModel/AnimatedModelsModule.h
  ../src/AnimatedModels/SdkModel/CMakeLists.txt
  ../src/AnimatedModels/SdkModel/IAnimatedModel.h
  ../src/AnimatedModels/SdkModel/IAnimatedModelsController.h
  ../src/AnimatedModels/SdkModel/IAnimatedModelsFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\AnimatedModels\\SdkModel FILES ${currsources})
