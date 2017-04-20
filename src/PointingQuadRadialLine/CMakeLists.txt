set(headers ${headers} ../src/PointingQuadRadialLine
)
set(currsources
  ../src/PointingQuadRadialLine/QuadLine.h  ../src/PointingQuadRadialLine/QuadLine.cpp
  ../src/PointingQuadRadialLine/QuadLineFactory.h  ../src/PointingQuadRadialLine/QuadLineFactory.cpp
  ../src/PointingQuadRadialLine/QuadLineMeshUnlitColorMaterial.h  ../src/PointingQuadRadialLine/QuadLineMeshUnlitColorMaterial.cpp
  ../src/PointingQuadRadialLine/QuadLineRenderable.h  ../src/PointingQuadRadialLine/QuadLineRenderable.cpp
  ../src/PointingQuadRadialLine/TriangleGeometryHelpers.h  ../src/PointingQuadRadialLine/TriangleGeometryHelpers.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\PointingQuadRadialLine FILES ${currsources})
