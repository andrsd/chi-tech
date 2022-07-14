file (GLOB MORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/GolubFisher/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/PETScUtils/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/Conical/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/Jacobi/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/LegendrePoly/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/LegendrePoly/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/SLDFESQ/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/RandomNumberGeneration/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SerialNewtonIteration/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SparseMatrix/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SpatialDiscretization/CellMappings/FE_PWL/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SpatialDiscretization/FiniteElement/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SpatialDiscretization/FiniteElement/PiecewiseLinear/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/SpatialDiscretization/FiniteVolume/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Statistics/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/UnknownManager/*.cc"
)

if(CHITECH_WITH_LUA)
    file (GLOB LUA_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/LegendrePoly/lua/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/Quadratures/SLDFESQ/lua/*.cc"
    )
    FOREACH(item ${LUA_SOURCES})
        IF(${item} MATCHES "Quadratures/SLDFESQ/lua/sldfesq_maindoc_page.cc")
            LIST(REMOVE_ITEM LUA_SOURCES ${item})
        ENDIF()
    ENDFOREACH(item)
endif()

set(SOURCES ${SOURCES} ${MORE_SOURCES} ${LUA_SOURCES} PARENT_SCOPE)


#set_source_files_properties(chi_console_00_constrdestr.cc PROPERTIES COMPILE_FLAGS -Wno-effc++)
