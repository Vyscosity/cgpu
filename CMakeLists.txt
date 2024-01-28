cmake_minimum_required(VERSION 3.0)
project(untitled C)

set(SDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL)
add_subdirectory(deps)

include(deps/bgfx.cmake/cmake/util/ConfigureDebugging.cmake)

file(GLOB_RECURSE src "src/*.c")
list(FILTER src EXCLUDE REGEX "src/main.c")  # Exclude Main.cpp from the source files

# Add the executable and link against the necessary libraries

add_executable(game ${src} src/main.c ${PROJECT_SOURCE_DIR}/res/shaders/fs_cubes.sc ${PROJECT_SOURCE_DIR}/res/shaders/vs_cubes.sc)

add_shader( ${PROJECT_SOURCE_DIR}/res/shaders/vs_cubes.sc VERTEX   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders DX11_MODEL 5_0 GLSL 130 )
add_shader( ${PROJECT_SOURCE_DIR}/res/shaders/fs_cubes.sc FRAGMENT OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders DX11_MODEL 5_0 GLSL 130 )


target_link_libraries(game PRIVATE SDL2main SDL2-static bgfx)

target_include_directories(game PRIVATE src "${SDL_DIR}/include")

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
