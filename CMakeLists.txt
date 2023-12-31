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
        Camera.cpp
        World.cpp
        Observer.cpp
        GUI/Game.cpp
        GUI/EntityView.cpp
        GUI/GUIWall.cpp
        GUI/ConcreteFactory.cpp
        AbstractFactory.cpp
        Stopwatch.cpp
        GUI/GUIPacMan.cpp
        PacMan.cpp
        Coin.cpp
        GUI/GUICoin.cpp
        GUI/StateManager.cpp
        GUI/State.cpp
        GUI/MenuState.cpp
        GUI/LevelState.cpp
        GUI/VictoryState.cpp
        GUI/PausedState.cpp
        GUI/GUIGhost.cpp
        Fruit.cpp
        Random.cpp
        GhostStateManager.cpp
        GhostIdleState.cpp
        GhostState.cpp
        GhostChasingState.cpp
        GhostFrightenedState.cpp
        GhostResetState.cpp
        GUI/GUIFruit.cpp
        GhostEatenState.cpp
        GUI/Window.cpp
        GUI/GameOverState.cpp
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
TARGET_LINK_LIBRARIES(Pac-Man sfml-system sfml-window sfml-graphics sfml-audio)