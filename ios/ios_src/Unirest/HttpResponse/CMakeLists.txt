if(${IOS})
set(headers ${headers} ios_src/Unirest/HttpResponse
)
set(currsources
  ios_src/Unirest/HttpResponse/CMakeLists.txt
  ios_src/Unirest/HttpResponse/UNIHTTPBinaryResponse.h
  ios_src/Unirest/HttpResponse/UNIHTTPBinaryResponse.m
  ios_src/Unirest/HttpResponse/UNIHTTPJsonResponse.h
  ios_src/Unirest/HttpResponse/UNIHTTPJsonResponse.m
  ios_src/Unirest/HttpResponse/UNIHTTPResponse.h
  ios_src/Unirest/HttpResponse/UNIHTTPResponse.m
  ios_src/Unirest/HttpResponse/UNIHTTPStringResponse.h
  ios_src/Unirest/HttpResponse/UNIHTTPStringResponse.m
  ios_src/Unirest/HttpResponse/UNIJsonNode.h
  ios_src/Unirest/HttpResponse/UNIJsonNode.m)
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc -w")
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Unirest\\HttpResponse FILES ${currsources})
endif(${IOS})
