cmake_minimum_required(VERSION 3.22)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "Build for 10.13")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_STANDALONE "Build standalone plugin format" ON)

if(DEFINED ENV{VERSION})
    set(PROJECT_VERSION $ENV{VERSION})
else()
    set(PROJECT_VERSION "0.0.1")
endif()

project(Setekh VERSION ${PROJECT_VERSION})

set(plugin_formats AU VST3 LV2)
if(BUILD_STANDALONE)
    list(APPEND plugin_formats Standalone)
endif()

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "Full FX Media"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    JUCE_VST3_CAN_REPLACE_VST2 FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE FFXM
    PLUGIN_CODE SETK
    FORMATS ${plugin_formats}
    PRODUCT_NAME "Setekh"
    PLUGIN_DESCRIPTION "A minimalistic yet sonically powerful distortion plugin"
    LV2URI "https://fullfxmedia.com/plugins/setekh"
    BUNDLE_ID "com.fullfxmedia.setekh"
)

clap_juce_extensions_plugin(
    TARGET ${PROJECT_NAME}
    CLAP_ID "com.fullfxmedia.setekh"
    CLAP_FEATURES audio-effect dynamics
)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        source/*.cpp
)

file(GLOB RESOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/*"
)

juce_add_binary_data(BinaryData
    SOURCES ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE BinaryData)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCES}
)

get_target_property(juce_generated_code_dir ${PROJECT_NAME} JUCE_GENERATED_SOURCES_DIRECTORY)
if(NOT juce_generated_code_dir)
    message(FATAL_ERROR "Failed to locate JUCE generated sources for target ${PROJECT_NAME}")
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${juce_generated_code_dir}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

juce_generate_juce_header(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${plugin_sources}
        ${plugin_headers}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_core
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_audio_formats
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_PLUGINHOST_VST=0
)

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum macOS deployment version" FORCE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC JUCE_AU=1)
endif()

