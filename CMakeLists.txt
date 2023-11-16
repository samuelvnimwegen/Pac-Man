cmake_minimum_required(VERSION 3.26)
project(Pac-Man)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pac-Man main.cpp
        Subject.cpp
        Score.cpp
        EntityModel.cpp
        Ghost.cpp
        Wall.cpp
        Collectable.cpp
        PacMan.cpp
        Camera.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
TARGET_LINK_LIBRARIES(Pac-Man sfml-system sfml-window sfml-graphics sfml-audio)