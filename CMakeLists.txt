#------------------------------------------------------------------------------
# CMakeLists.txt
# By Quentin Bazin
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.8)

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
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wfatal-errors")

#------------------------------------------------------------------------------
# Packages
#------------------------------------------------------------------------------
# - Qt5
#------------------------------------------------------------------------------
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

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
               ${SOURCE_FILES}
               ${HEADER_FILES})

#------------------------------------------------------------------------------
# Link options
#------------------------------------------------------------------------------
target_link_libraries(${CMAKE_PROJECT_NAME}
                      ${CPR_LIBRARIES}
                      ${CURL_LIBRARIES}
                      ${QTKEYCHAIN_LIBRARIES})

QT5_USE_MODULES(${CMAKE_PROJECT_NAME} Widgets)

#------------------------------------------------------------------------------
# Install paths
#------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_INSTALL_BINDIR)
  set(CMAKE_INSTALL_BINDIR bin)
endif()

install(TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

