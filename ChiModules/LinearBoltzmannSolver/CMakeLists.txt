file (GLOB MORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Groupset/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/IterativeMethods/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/IterativeOperations/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/PointSource/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SweepChunks/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Tools/*.cc"
)

if(CHITECH_WITH_LUA)
    file (GLOB LUA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cc")
endif()

set(SOURCES ${SOURCES} ${MORE_SOURCES} ${LUA_SOURCES} PARENT_SCOPE)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Groupset")

#set_source_files_properties(chi_console_00_constrdestr.cc PROPERTIES COMPILE_FLAGS -Wno-effc++)
