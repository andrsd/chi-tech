cmake_minimum_required(VERSION 3.12)

#================================================ Set project targets
SET(TARGET ChiTech)
project(${TARGET} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(CHITECH_WITH_VTK "Build with VTK support" YES)
option(CHITECH_WITH_LUA "Build with Lua support" YES)
option(BUILD_SHARED_LIBS "Build as a shared library" NO)

message(STATUS "Configuring ${CMAKE_BUILD_TYPE} build of ChiTech.")

if(UNIX AND NOT APPLE)
    add_definitions(-DUNIX_ENV)
elseif(APPLE)
    add_definitions(-DAPPLE_ENV)
    add_definitions(-DUNIX_ENV)
else()
    add_definitions(-DWINDOWS_ENV)
endif()

#------------------------------------------------ DEPENDENCIES
if (NOT DEFINED PETSC_ROOT)
    if (NOT (DEFINED ENV{PETSC_ROOT}))
        message(FATAL_ERROR "***** PETSC_ROOT is not set *****")
    else()
        set(PETSC_ROOT "$ENV{PETSC_ROOT}")
    endif()
endif()
message(STATUS "PETSC_ROOT set to ${PETSC_ROOT}")

if (CHITECH_WITH_LUA)
    if (NOT DEFINED LUA_ROOT)
        if (NOT (DEFINED ENV{LUA_ROOT}))
            find_package(Lua REQUIRED)
        else()
            set(LUA_ROOT "$ENV{LUA_ROOT}")
        endif()
    endif()
    if (DEFINED LUA_ROOT)
        message(STATUS "LUA_ROOT set to ${LUA_ROOT}")
    endif()
endif()

if (CHITECH_WITH_VTK)
    if (NOT DEFINED VTK_DIR)
        if (NOT (DEFINED ENV{VTK_DIR}))
            message(FATAL_ERROR "***** VTK_DIR is not set *****")
        else()
            set(VTK_DIR "$ENV{VTK_DIR}")
        endif()
    endif()
    message(STATUS "VTK_DIR set to ${VTK_DIR}")
endif()

#================================================ Set variables
set(CHI_TECH_DIR "${PROJECT_SOURCE_DIR}")
set(CHI_TECH_MOD "ChiModules")

#================================================ Set cmake variables
find_package(MPI)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/ChiResources/Macros")

if (NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
endif()

#================================================ Export vars to config file
set(CONFIG_FILE_NAME "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.cmake")
file(WRITE "${CONFIG_FILE_NAME}"
    "# Environment configuration file for ChiTech.\n")
file(APPEND "${CONFIG_FILE_NAME}" "set(PETSC_ROOT ${PETSC_ROOT})\n")
if (DEFINED LUA_ROOT)
    file(APPEND "${CONFIG_FILE_NAME}" "set(LUA_ROOT ${LUA_ROOT})\n")
endif()
if(CHITECH_WITH_VTK)
    file(APPEND "${CONFIG_FILE_NAME}" "set(VTK_DIR ${VTK_DIR})\n")
endif()

#================================================ Include macros
include(GNUInstallDirs)
include(Filter)
include(Checks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

#================================================ Default include directories
include_directories(SYSTEM ${MPI_CXX_INCLUDE_PATH})
if (CHITECH_WITH_LUA)
    if (DEFINED LUA_ROOT)
        include_directories(SYSTEM "${LUA_ROOT}/include")
    else()
        include_directories(SYSTEM ${LUA_INCLUDE_DIR})
    endif()
endif()
include_directories(SYSTEM "${PETSC_ROOT}/include")

include_directories(SYSTEM "${CHI_TECH_DIR}/ThirdParty/paraview")

include_directories(${PROJECT_BINARY_DIR})
include_directories("${CHI_TECH_DIR}/ChiTech")
include_directories("${CHI_TECH_DIR}/ChiTech/ChiLua")
include_directories("${CHI_TECH_DIR}/ChiTech/ChiMPI")
include_directories("${CHI_TECH_DIR}/ChiTech/ChiLog")
include_directories("${CHI_TECH_DIR}/ChiTech/ChiMiscUtils")
include_directories("${CHI_TECH_DIR}/ChiResources")
include_directories("${CHI_TECH_DIR}/ChiModules")

#================================================ Library directories
set(CHI_LIBS stdc++ m dl ${MPI_CXX_LIBRARIES} petsc)

if (CHITECH_WITH_LUA)
    if (DEFINED LUA_ROOT)
        link_directories("${LUA_ROOT}/lib")
        set(LUA_LIBRARIES lua)
    endif()
    list(APPEND CHI_LIBS ${LUA_LIBRARIES})
endif()

link_directories("${PETSC_ROOT}/lib")

# --------------------------- VTK
if(CHITECH_WITH_VTK)
    find_package(VTK PATHS ${VTK_DIR} QUIET)
    message (STATUS "VTK_VERSION: ${VTK_VERSION}")
    if (NOT VTK_FOUND)
        message(FATAL_ERROR "VTK not found: ${VTK_NOT_FOUND_MESSAGE}")
    endif()

    if (VTK_VERSION VERSION_LESS "8.90.0")
        find_package(VTK COMPONENTS
                vtkCommonCore vtkCommonDataModel
                vtkIOLegacy vtkIOCore
                vtkIOXML vtkParallelCore vtkIOParallelXML
                vtkFiltersCore
                vtkIOEnSight
                REQUIRED PATHS ${VTK_DIR})
        # old system
        include(${VTK_USE_FILE})
        include_directories(SYSTEM ${VTK_INCLUDE_DIRS})
    else ()
        find_package(VTK COMPONENTS
                CommonCore CommonDataModel
                IOLegacy IOCore
                IOXML ParallelCore IOParallelXML
                FiltersCore
                IOEnSight
                REQUIRED PATHS ${VTK_DIR})
        # vtk_module_autoinit is needed
        vtk_module_autoinit(TARGETS ${TARGET} MODULES ${VTK_LIBRARIES})
    endif()
    list(APPEND CHI_LIBS ${VTK_LIBRARIES})
endif()

#================================================ Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
# Force -O3 in release builds (some OS's might downgrade it)
string(REPLACE "-O2" "-O3" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
string(REPLACE "-O2" "-O3" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
string(REPLACE "-O2" "-O3" CMAKE_CXX_FLAGS_MINSIZEREL ${CMAKE_CXX_FLAGS_MINSIZEREL})

set(CHI_CXX_FLAGS)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND CHI_CXX_FLAGS "-pedantic")
    list(APPEND CHI_CXX_FLAGS "-Wall")
    list(APPEND CHI_CXX_FLAGS "-Wno-unused-variable")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    list(APPEND CHI_CXX_FLAGS "-pedantic")
    list(APPEND CHI_CXX_FLAGS "-Wall")
    list(APPEND CHI_CXX_FLAGS "-Wno-unused-variable")
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    list(APPEND CHI_CXX_FLAGS "-pedantic")
    list(APPEND CHI_CXX_FLAGS "-Wall")
    list(APPEND CHI_CXX_FLAGS "-Wno-unused-variable")
    list(APPEND CHI_CXX_FLAGS "-Wno-sign-compare")
    list(APPEND CHI_CXX_FLAGS "-Wno-psabi")
#elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel")
#elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
else()
    message(WARNING "Untested CMAKE_CXX_COMPILER_ID : ${CMAKE_CXX_COMPILER_ID}")
endif()

#================================================ Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS}")

#================================================ Define source directories
set(SOURCES "${CHI_TECH_DIR}/ChiTech/chi_runtime.cc")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiConsole")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiLua")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiMath")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiPhysics")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiGraph")

add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiTimer")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiMesh")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiMPI")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiLog")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiDataTypes")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/ChiMiscUtils")
add_subdirectory("${CHI_TECH_DIR}/ChiTech/LuaTest")

add_subdirectory("${CHI_TECH_MOD}")

#================================================ Define targets
add_library(ChiLib ${SOURCES})
target_link_libraries(ChiLib PUBLIC ${CHI_LIBS})
target_compile_options(ChiLib PUBLIC ${CHI_CXX_FLAGS})
set_target_properties(ChiLib PROPERTIES MACOSX_RPATH OFF)
set_target_properties(ChiLib PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set_target_properties(ChiLib PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
if(CHITECH_WITH_LUA)
    target_compile_definitions(ChiLib PUBLIC CHITECH_HAVE_LUA)
endif()
if(CHITECH_WITH_VTK)
    target_compile_definitions(ChiLib PUBLIC CHITECH_HAVE_VTK)
endif()

#================================================ Third-party library
add_subdirectory("${CHI_TECH_DIR}/ThirdParty")
if(CHITECH_WITH_VTK)
    target_link_libraries(ChiLib PRIVATE ThirdParty)
endif()

if(CHITECH_WITH_LUA)
    add_executable(${TARGET} "${CHI_TECH_DIR}/ChiTech/chi_tech_main.cc")
    target_link_libraries(${TARGET} ChiLib)
    target_compile_options(${TARGET} PUBLIC ${CHI_CXX_FLAGS})
endif()

# |------------ Write Makefile to root directory
file(WRITE ${PROJECT_SOURCE_DIR}/Makefile "subsystem:\n" "\t$(MAKE) -C chi_build \n\n"
        "clean:\n\t$(MAKE) -C chi_build clean\n")

#================================================ Config

if(CHITECH_WITH_LUA)
  set(CHITECH_HAVE_LUA ${CHITECH_WITH_LUA})
endif()
if(CHITECH_WITH_VTK)
  set(CHITECH_HAVE_VTK ${CHITECH_WITH_VTK})
endif()

configure_file(ChiTech/chitech_config.h.in chitech_config.h)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ChiResources/Macros/ChiTechConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ChiTechConfig.cmake
    INSTALL_DESTINATION lib/cmake/ChiTech
)

install(
    TARGETS ChiLib
    EXPORT ChiTechTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(CHITECH_WITH_VTK)
  install(
      TARGETS ThirdParty
      EXPORT ChiTechTargets
      LIBRARY DESTINATION lib
  )
endif()

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/ChiModules/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChiTech/ChiModules
    FILES_MATCHING PATTERN "*.h"
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/ChiTech/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChiTech/ChiTech
    FILES_MATCHING PATTERN "*.h"
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/chitech_config.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChiTech
)

include(CMakePackageConfigHelpers)

install(
    EXPORT ChiTechTargets
    FILE ChiTechTargets.cmake
    NAMESPACE ChiTech::
    DESTINATION lib/cmake/ChiTech
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/ChiTechConfig.cmake"
    DESTINATION lib/cmake/ChiTech
)
