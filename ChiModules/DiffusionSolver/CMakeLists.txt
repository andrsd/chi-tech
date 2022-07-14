file (GLOB MORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Boundaries/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Solver/*.cc"
)

if(CHITECH_WITH_LUA)
    file (GLOB LUA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cc")

    FOREACH(item ${LUA_SOURCES})
        IF(${item} MATCHES "lua/diffusion_maindoc_page.cc")
            LIST(REMOVE_ITEM LUA_SOURCES ${item})
        ENDIF()
    ENDFOREACH(item)
endif()

set(SOURCES ${SOURCES} ${MORE_SOURCES} ${LUA_SOURCES} PARENT_SCOPE)


#set_source_files_properties(chi_console_00_constrdestr.cc PROPERTIES COMPILE_FLAGS -Wno-effc++)
