#------------------------------------------------------------------------------
# CMakeLists.txt
# By Quentin Bazin
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)

project(eifl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#------------------------------------------------------------------------------
# Get source files
#------------------------------------------------------------------------------
file(GLOB_RECURSE SOURCE_FILES source/*.cpp external/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp external/*.hpp)

foreach(HEADER_FILE ${HEADER_FILES})
	get_filename_component(HEADER_DIRECTORY ${HEADER_FILE} DIRECTORY)
	include_directories(${HEADER_DIRECTORY})
endforeach(HEADER_FILE)

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors")

#------------------------------------------------------------------------------
# Packages
#------------------------------------------------------------------------------
# - Qt5
#------------------------------------------------------------------------------
find_package(Qt5 COMPONENTS Widgets Keychain REQUIRED)

include_directories(${Qt5_INCLUDE_DIRS})
add_definitions(${Qt5_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)

#------------------------------------------------------------------------------
# - QtKeychain
#------------------------------------------------------------------------------
find_package(Qt5Keychain REQUIRED)

include_directories(${QTKEYCHAIN_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# - cpr
#------------------------------------------------------------------------------
find_package(CURL REQUIRED)
find_package(CPR REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})
include_directories(${CPR_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# Add executable
#------------------------------------------------------------------------------
add_executable(${CMAKE_PROJECT_NAME}
               ${SOURCE_FILES})

#------------------------------------------------------------------------------
# Link options
#------------------------------------------------------------------------------
target_link_libraries(${CMAKE_PROJECT_NAME}
                      ${CURL_LIBRARIES}
                      ${CPR_LIBRARIES}
                      ${QTKEYCHAIN_LIBRARIES}
                      Qt5::Widgets)

