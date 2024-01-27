cmake_minimum_required(VERSION 3.0)
project(untitled)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL)
add_subdirectory(deps)

include(deps/bgfx.cmake/cmake/util/ConfigureDebugging.cmake)

file(GLOB_RECURSE src "src/*.cpp")
list(FILTER src EXCLUDE REGEX "src/Main.cpp")  # Exclude Main.cpp from the source files

# Add the executable and link against the necessary libraries

add_executable(game ${src} src/Main.cpp ${PROJECT_SOURCE_DIR}/res/shaders/fs_cubes.sc ${PROJECT_SOURCE_DIR}/res/shaders/vs_cubes.sc)

add_shader( ${PROJECT_SOURCE_DIR}/res/shaders/vs_cubes.sc VERTEX   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders DX11_MODEL 5_0 GLSL 130 )
add_shader( ${PROJECT_SOURCE_DIR}/res/shaders/fs_cubes.sc FRAGMENT OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders DX11_MODEL 5_0 GLSL 130 )


target_link_libraries(game PRIVATE SDL2main SDL2-static bgfx glm)

target_include_directories(game PRIVATE src "${SDL_DIR}/include")

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
