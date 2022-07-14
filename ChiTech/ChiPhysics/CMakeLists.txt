file (GLOB MORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/BasicOptions/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/FieldFunction/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/PhysicsMaterial/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/PhysicsMaterial/transportxsections/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SolverBase/*.cc"
)

FOREACH(item ${MORE_SOURCES})
    IF(${item} MATCHES "FieldFunction/fieldfunction_maindoc.cc")
        LIST(REMOVE_ITEM MORE_SOURCES ${item})
    ENDIF()
ENDFOREACH(item)

if(CHITECH_WITH_LUA)
    file (GLOB LUA_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/FieldFunction/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/PhysicsMaterial/transportxsections/lua/*.cc"
    )
    FOREACH(item ${LUA_SOURCES})
        IF(${item} MATCHES "lua/physics_maindoc_page.cc")
            LIST(REMOVE_ITEM LUA_SOURCES ${item})
        ENDIF()
    ENDFOREACH(item)
else()
    FOREACH(item ${MORE_SOURCES})
        IF(${item} MATCHES "PhysicsMaterial/transportxsections/prop_transportxs_05_pushlua.cc" OR
           ${item} MATCHES "PhysicsMaterial/material_property_base.cc" OR
           ${item} MATCHES "chi_physics_physics_loop.cpp")
            LIST(REMOVE_ITEM MORE_SOURCES ${item})
        ENDIF()
    ENDFOREACH(item)
endif()

set(SOURCES ${SOURCES} ${MORE_SOURCES} ${LUA_SOURCES} PARENT_SCOPE)

#set_source_files_properties(chi_console_00_constrdestr.cc PROPERTIES COMPILE_FLAGS -Wno-effc++)
