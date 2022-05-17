cmake_minimum_required(VERSION 3.15)
project(RubamazzettoClient VERSION 1.0)


find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 11) # Requires C11 standard

# Set header file include path
include_directories( ${PROJECT_SOURCE_DIR}/include )

# Traversal file
file(GLOB_RECURSE all_source source/*.c)

add_compile_options(-mcmodel=medium -m64)

# Generate target executable
add_executable(RubamazzettoClient ${all_source})

target_link_libraries(${PROJECT_NAME} raylib m)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
target_link_libraries(${PROJECT_NAME} "-framework IOKit")
target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

enable_testing()

file(GLOB_RECURSE test_files test/*.c)
list(REMOVE_ITEM all_source "${PROJECT_SOURCE_DIR}/source/main.c")

foreach(test_file ${test_files})
    get_filename_component(test_file_we ${test_file} NAME_WE)

    include_directories( ${PROJECT_SOURCE_DIR}/include )
    add_compile_options(-mcmodel=large -m64)
    add_executable(${test_file_we} ${test_file} ${all_source})
    target_link_libraries(${test_file_we} raylib m)
    add_test(${test_file_we} ${test_file_we})
endforeach()



