file (GLOB MORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Cell/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/DomainDecomposition/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/FieldFunctionInterpolation/Line/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/FieldFunctionInterpolation/Slice/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/FieldFunctionInterpolation/Volume/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/LineMesh/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/LogicalVolume/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/MeshContinuum/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/MeshCutting/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/MeshHandler/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/OrthoGrids/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Raytrace/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Region/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SurfaceMesh/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SurfaceMesher/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SurfaceMesher/Delaunay/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SurfaceMesher/PassThrough/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SurfaceMesher/Predefined/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/AngleAggregation/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/AngleSet/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/AngleSetGroup/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/FLUDS/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/SPDS/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/SPLS/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/SweepBoundary/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/SweepBuffer/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepUtilities/SweepScheduler/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/UnpartitionedMesh/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/VolumeMesher/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/VolumeMesher/Extruder/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/VolumeMesher/PredefinedUnpartitioned/*.cc"
)
FOREACH(item ${MORE_SOURCES})
    IF(${item} MATCHES "UnpartitionedMesh/unpartmesh_ortho_cutting.cc")
        LIST(REMOVE_ITEM MORE_SOURCES ${item})
    ENDIF()
ENDFOREACH(item)

if(CHITECH_WITH_LUA)
    file (GLOB LUA_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/DomainDecomposition/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/FieldFunctionInterpolation/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/LineMesh/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/LogicalVolume/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/MeshCutting/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/MeshHandler/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/OrthoGrids/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/Region/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/SurfaceMesh/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/SurfaceMesher/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/UnpartitionedMesh/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/VolumeMesher/lua/*.cc"
    )
    FOREACH(item ${LUA_SOURCES})
        IF(${item} MATCHES "lua/mesh_maindoc_page.cc")
            LIST(REMOVE_ITEM LUA_SOURCES ${item})
        ENDIF()
    ENDFOREACH(item)
else()
  FOREACH(item ${MORE_SOURCES})
      IF(${item} MATCHES "FieldFunctionInterpolation/Volume/chi_ffinter_volume_calllua.cc")
          LIST(REMOVE_ITEM MORE_SOURCES ${item})
      ENDIF()
  ENDFOREACH(item)
endif()

set(SOURCES ${SOURCES} ${MORE_SOURCES} ${LUA_SOURCES} PARENT_SCOPE)

#set_source_files_properties(chi_console_00_constrdestr.cc PROPERTIES COMPILE_FLAGS -Wno-effc++)
