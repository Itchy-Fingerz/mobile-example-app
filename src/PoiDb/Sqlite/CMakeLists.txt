set(headers ${headers} ../src/PoiDb/Sqlite
)
set(currsources
  ../src/PoiDb/Sqlite/SqliteDbConnection.cpp
  ../src/PoiDb/Sqlite/SqliteDbConnection.h
  ../src/PoiDb/Sqlite/SqliteTable.cpp
  ../src/PoiDb/Sqlite/SqliteTable.h
  ../src/PoiDb/Sqlite/SqliteQueryBuilder.h
  ../src/PoiDb/Sqlite/SqliteQueryBuilder.cpp
  ../src/PoiDb/Sqlite/SqliteTableQuery.h
  ../src/PoiDb/Sqlite/SqliteTableQuery.cpp
  ../src/PoiDb/Sqlite/Sqlite.h
  ../src/PoiDb/Sqlite/CMakeLists.txt

)
set(sources ${sources} ${currsources})
source_group(\\src\\PoiDb\\Sqlite FILES ${currsources})
