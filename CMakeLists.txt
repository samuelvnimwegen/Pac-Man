cmake_minimum_required(VERSION 3.26)
project(Pac-Man)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pac-Man
        main.cpp
        Model/Subject.cpp
        Model/Score.cpp
        Model/EntityModel.cpp
        Model/Ghost.cpp
        Model/Wall.cpp
        Model/Collectable.cpp
        GUI/Camera.cpp
        Model/World.cpp
        Model/Observer.cpp
        GUI/Game.cpp
        GUI/EntityView.cpp
        GUI/GUIWall.cpp
        GUI/ConcreteFactory.cpp
        Model/AbstractFactory.cpp
        Model/Stopwatch.cpp
        GUI/GUIPacMan.cpp
        Model/PacMan.cpp
        Model/Coin.cpp
        GUI/GUICoin.cpp
        GUI/StateManager.cpp
        GUI/State.cpp
        GUI/MenuState.cpp
        GUI/LevelState.cpp
        GUI/VictoryState.cpp
        GUI/PausedState.cpp
        GUI/GUIGhost.cpp
        Model/Fruit.cpp
        Model/Random.cpp
        Model/GhostStateManager.cpp
        Model/GhostIdleState.cpp
        Model/GhostState.cpp
        Model/GhostChasingState.cpp
        Model/GhostFrightenedState.cpp
        Model/GhostResetState.cpp
        GUI/GUIFruit.cpp
        Model/GhostEatenState.cpp
        GUI/Window.cpp
        GUI/GameOverState.cpp
        Model/GhostIdleFrightenedState.cpp
        Model/AbstractFactory.cpp
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
TARGET_LINK_LIBRARIES(Pac-Man sfml-system sfml-window sfml-graphics sfml-audio)