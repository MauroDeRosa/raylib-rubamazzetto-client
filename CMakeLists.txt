cmake_minimum_required(VERSION 3.15)
project(RubamazzettoClient VERSION 1.0)


find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 11) # Requires C11 standard


# Set header file include path
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Traversal file
file(GLOB_RECURSE all_files
source/*.cpp
source/*.cc
source/*.c
test/*.cpp
test/*.cc
test/*.c)

# Generate target executable
add_executable(RubamazzettoClient ${all_files})

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
target_link_libraries(${PROJECT_NAME} "-framework IOKit")
target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()





