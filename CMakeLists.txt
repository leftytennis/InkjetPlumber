cmake_minimum_required(VERSION 3.22)

project(InkjetPlumber)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/Sparkle/build/Release/Sparkle.framework/Versions/Current/Headers")

set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)
set(ONLY_ACTIVE_ARCH NO)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
#set(SPARKLE_DIR "${CMAKE_SOURCE_DIR}/src/Sparkle/Sparkle")

file(GLOB SPARKLE_HINT "${CMAKE_SOURCE_DIR}/src/Sparkle/build/Release/Sparkle.framework/")

find_path(SPARKLE_INCLUDE_DIR Sparkle.h
  HINTS ${SPARKLE_HINT}
)

find_library(SPARKLE_LIBRARY NAMES Sparkle
  HINTS ${SPARKLE_HINT}
)

include_directories(${SOURCE_DIR})
include_directories(${SPARKLE_INCLUDE_DIR})

find_package(Qt6 6.2.2 REQUIRED COMPONENTS Core Gui PrintSupport)
#find_package(Sparkle REQUIRED)

file(GLOB SOURCES
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.h"
    "${SOURCE_DIR}/*.iu"
    "${SOURCE_DIR}/*.mm"
    "${SOURCE_DIR}/*.qrc"
)

add_executable(InkjetPlumber MACOSX_BUNDLE
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::PrintSupport
    ${SPARKLE_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER org.threeputt.${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}.plist
)
