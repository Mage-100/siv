cmake_minimum_required(VERSION 4.1)

project(
    siv
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(SDL_STATIC ON)

set(EXECUTABLE_NAME siv)

add_subdirectory("./dependencies/SDL" EXCLUDE_FROM_ALL)

add_executable(${EXECUTABLE_NAME} src/main.c)
target_include_directories(${EXECUTABLE_NAME} PRIVATE
    "./include"
    "./dependencies/SDL/include"
)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3::SDL3-static)
