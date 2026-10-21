# -------------------------------
# General settings
# -------------------------------

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(selection_script VERSION 1.0)

# -------------------------------
# External dependencies
# -------------------------------

# ROOT
find_package(ROOT REQUIRED COMPONENTS Core RIO Hist Tree Geom Physics Matrix MathCore Spectrum Graf Gpad)

# CMake
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# -------------------------------
# fiTQun output library
# -------------------------------

add_library(fiTQun_dict SHARED ${CMAKE_SOURCE_DIR}/include/fiTQun_project/fiTQun_projectProjectSource.cxx)

target_include_directories(fiTQun_dict
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(fiTQun_dict
  PUBLIC
    ROOT::Core
    ROOT::RIO
    ROOT::Tree
)

ROOT_GENERATE_DICTIONARY(G__fiTQun_dict
  include/fiTQun_project/fiTQun_projectProjectHeaders.h
  MODULE fiTQun_dict
  LINKDEF include/fiTQun_project/fiTQun_projectLinkDef.h
)

# -------------------------------
# Create main library with header and source files
# -------------------------------

add_library(selection_script_lib)

# Header and source files are added here
target_sources(selection_script_lib
  PRIVATE
    src/base/BasefiTQunAnalysis.cpp
    src/base/AnafiTQunEvent.cpp

    src/analysis/fiTQunEventCheck.cpp

    src/utils/FillInfoUtils.cpp
    src/utils/CategoryUtils.cpp
    src/utils/GeomUtils.cpp
    src/utils/SelectionUtils.cpp
)

target_include_directories(selection_script_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

# Link dependent libraries
target_link_libraries(selection_script_lib
  PUBLIC
    ROOT::Core
    ROOT::RIO
    ROOT::Hist
    ROOT::Tree
    ROOT::Geom
    ROOT::Physics
    ROOT::Matrix
    ROOT::MathCore
    ROOT::Spectrum
    ROOT::Graf
    ROOT::Gpad
    ROOT::TreePlayer
)

target_link_libraries(selection_script_lib PUBLIC fiTQun_dict)

add_library(selection_script::selection_script_lib ALIAS selection_script_lib)

# -------------------------------
# Create executables
# -------------------------------

add_executable(RunfiTQunEventCheck app/RunfiTQunEventCheck.cpp)

# Link to the library created above
target_link_libraries(RunfiTQunEventCheck PRIVATE selection_script_lib)

# -------------------------------
# Install configurations
# -------------------------------

install(TARGETS fiTQun_dict
  EXPORT selection_scriptTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/libfiTQun_dict_rdict.pcm
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  OPTIONAL
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/libfiTQun_dict.rootmap
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  OPTIONAL
)

install(TARGETS selection_script_lib
  EXPORT selection_scriptTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Executable install is added here
install(TARGETS RunfiTQunEventCheck 
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/selection_scriptConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(EXPORT selection_scriptTargets
  FILE selection_scriptTargets.cmake
  NAMESPACE selection_script::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/selection_script
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/selection_scriptConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/selection_scriptConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/selection_script
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/selection_scriptConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/selection_scriptConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/selection_script
)
