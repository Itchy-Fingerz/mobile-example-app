set(headers ${headers} Include/Crashlytics
)
set(currsources
Include/Crashlytics/CMakeLists.txt
Include/Crashlytics/Crashlytics.framework
Include/Crashlytics/Fabric.framework
)
set(sources ${sources} ${currsources})
source_group(\\Crashlytics FILES ${currsources})
