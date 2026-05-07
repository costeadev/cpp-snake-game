cmake_minimum_required(VERSION 3.20)
project(snake_game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(snake_game main.cpp
        game.cpp
        render.cpp
        snake.cpp
        terminal.cpp)