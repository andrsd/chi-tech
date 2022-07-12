file (GLOB MORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/IterativeMethods/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/IterativeOperations/*.cc"
)

if(CHITECH_WITH_LUA)
    file (GLOB LUA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cc")
endif()

set(SOURCES ${SOURCES} ${MORE_SOURCES} ${LUA_SOURCES} PARENT_SCOPE)

#set_source_files_properties(chi_console_00_constrdestr.cc PROPERTIES COMPILE_FLAGS -Wno-effc++)
