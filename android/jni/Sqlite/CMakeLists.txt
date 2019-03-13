if(${ANDROID})
set(headers ${headers} jni/Sqlite
)
set(currsources
  jni/Sqlite/CMakeLists.txt
  jni/Sqlite/sqlite3.c
  jni/Sqlite/sqlite3.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Sqlite FILES ${currsources})
endif(${ANDROID})
