if(${IOS})
set(headers ${headers} ios_src/Unirest/HttpRequest
)
set(currsources
  ios_src/Unirest/HttpRequest/CMakeLists.txt
  ios_src/Unirest/HttpRequest/UNIBaseRequest.h
  ios_src/Unirest/HttpRequest/UNIBaseRequest.m
  ios_src/Unirest/HttpRequest/UNIBodyRequest.h
  ios_src/Unirest/HttpRequest/UNIBodyRequest.m
  ios_src/Unirest/HttpRequest/UNISimpleRequest.h
  ios_src/Unirest/HttpRequest/UNISimpleRequest.m
)
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc -w")
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Unirest\\HttpRequest FILES ${currsources})
endif(${IOS})
