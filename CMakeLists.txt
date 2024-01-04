cmake_minimum_required(VERSION 3.22.1)
project(Pac-Man)

set(CMAKE_CXX_STANDARD 17)

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio)

# Add include dirs for SFML
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

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
        Model/DijkstraGraph.cpp
        Model/DijkstraPoint.cpp
        Model/DijkstraTransition.cpp
        Model/EscapeWall.cpp
        GUI/GUIEscapeWall.cpp
)

# Link target to SFML libs
TARGET_LINK_LIBRARIES(Pac-Man sfml-system sfml-graphics sfml-window sfml-audio)

# Install our executable to the CMAKE_INSTALL_PREFIX/bin
INSTALL(TARGETS Pac-Man DESTINATION bin)
