add_subdirectory("DiffusionSolver")
add_subdirectory("LinearBoltzmannSolver")
add_subdirectory("LBSCurvilinear")
add_subdirectory("LBKEigenvalueSolver")
add_subdirectory("LBSAdjointSolver")

if(CHITECH_WITH_LUA)
    set(LUA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lua/chi_modules_lua.cc")
endif()

set(SOURCES ${SOURCES} ${LUA_SOURCES} PARENT_SCOPE)
