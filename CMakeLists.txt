cmake_minimum_required(VERSION 3.29.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

if (UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion")
endif (UNIX)

project(CosaTacToe CXX)

add_executable(${PROJECT_NAME}
               ./src/main.cpp
               ./src/cosaGame.cpp)

if (UNIX)
target_compile_options(${PROJECT_NAME} PRIVATE -O2 -std=c++20)
endif (UNIX)

