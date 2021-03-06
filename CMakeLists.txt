cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project(ld49 VERSION 0.3.1 LANGUAGES CXX)

# Add compiler flags for cmake.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Generate config file for clang.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Define colors
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColorReset "${Esc}[m")
  set(BoldRed    "${Esc}[1;31m")
endif()

# Prevent compilation in-source.
if(${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    Message(FATAL_ERROR "${BoldRed}Source and build directories are the same. \
Delete CMakeCache.txt, create an empty build directory, change into it and invoke 'cmake ..'${ColorReset}")
endif()

# For Windows, SFML is expected in the root directory.
if(WIN32)
  set(SFML_DIR "SFML/lib/cmake/SFML")
endif()
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

include_directories("src/main")
include_directories("src/entity")
include_directories("src/gamestate")
include_directories("src/environment")
include_directories("rapidjson/include")

# Source files
file(GLOB_RECURSE SRC "src/*.cpp")

# Create library and link
add_executable(ld49 ${SRC})
target_link_libraries(ld49 sfml-graphics sfml-audio)
target_link_libraries(ld49 ${OPENGL_LIBRARIES})
#target_link_libraries(ld49 "pthread")
