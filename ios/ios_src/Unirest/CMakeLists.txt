if(${IOS})
set(headers ${headers} ios_src/Unirest
)
set(currsources
  ios_src/Unirest/CMakeLists.txt
  ios_src/Unirest/Base64.h  ios_src/Unirest/Base64.m  ios_src/Unirest/UNIHTTPClientHelper.h  ios_src/Unirest/UNIHTTPClientHelper.m  ios_src/Unirest/UNIHTTPRequest.h  ios_src/Unirest/UNIHTTPRequest.m  ios_src/Unirest/UNIHTTPRequestWithBody.h  ios_src/Unirest/UNIHTTPRequestWithBody.m  ios_src/Unirest/Unirest-Prefix.pch  ios_src/Unirest/UNIRest.h  ios_src/Unirest/UNIRest.m  ios_src/Unirest/UNIUrlConnection.h  ios_src/Unirest/UNIUrlConnection.m
)
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc -w")
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Unirest FILES ${currsources})
include(ios_src/Unirest/HttpRequest/CMakeLists.txt)
include(ios_src/Unirest/HttpResponse/CMakeLists.txt)
endif(${IOS})
