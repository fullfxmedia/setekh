cmake_minimum_required(VERSION 3.26)

project(Setekh VERSION 0.0.1 LANGUAGES C CXX)

if (MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
include(cmake/cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 8.0.8
    VERSION 8.0.8
    SOURCE_DIR ${LIB_DIR}/juce
)

set(CLAP_JUCE_EXT_COMMIT 02f91b7)
CPMAddPackage(
    NAME ClapJuceExtensions
    VERSION 0.0.0-${CLAP_JUCE_EXT_COMMIT}
    GITHUB_REPOSITORY free-audio/clap-juce-extensions
    GIT_TAG ${CLAP_JUCE_EXT_COMMIT}
)

if (MSVC)
    add_compile_options(/Wall)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(plugin)
