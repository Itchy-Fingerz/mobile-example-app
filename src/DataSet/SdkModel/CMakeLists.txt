set(headers ${headers} ../src/DataSet/SdkModel
)
set(currsources
../src/DataSet/SdkModel/CMakeLists.txt
../src/DataSet/SdkModel/DataSet.h
../src/DataSet/SdkModel/DataSetController.cpp
../src/DataSet/SdkModel/DataSetController.h
../src/DataSet/SdkModel/DataSetCreationQuery.cpp
../src/DataSet/SdkModel/DataSetCreationQuery.h
../src/DataSet/SdkModel/DataSetCreationQueryFactory.cpp
../src/DataSet/SdkModel/DataSetCreationQueryFactory.h
../src/DataSet/SdkModel/DataSetCreationQueryModel.cpp
../src/DataSet/SdkModel/DataSetCreationQueryModel.h
../src/DataSet/SdkModel/DataSetModule.cpp
../src/DataSet/SdkModel/DataSetModule.h
../src/DataSet/SdkModel/IDatasetController.h
../src/DataSet/SdkModel/IDataSetCreationQuery.h
../src/DataSet/SdkModel/IDataSetCreationQueryFactory.h
../src/DataSet/SdkModel/DataSetInsertQuery.h../src/DataSet/SdkModel/DataSetInsertQueryFactory.h../src/DataSet/SdkModel/DataSetInsertQueryModel.h../src/DataSet/SdkModel/IDataSetInsertQuery.h../src/DataSet/SdkModel/IDataSetInsertQueryFactory.h../src/DataSet/SdkModel/DataSetInsertQuery.cpp../src/DataSet/SdkModel/DataSetInsertQueryFactory.cpp../src/DataSet/SdkModel/DataSetInsertQueryModel.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\DataSet\\SdkModel FILES ${currsources})
