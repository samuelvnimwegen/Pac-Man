//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GAME_H
#define PAC_MAN_GAME_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "iostream"
#include "vector"
#include "../Model/Observer.h"
#include "cassert"
#include "EntityView.h"
#include "Wall.h"
#include "ConcreteFactory.h"
#include "../GUI/Camera.h"
#include "PacMan.h"
#include "../Model/Stopwatch.h"
#include "Coin.h"
#include "StateManager.h"
#include "chrono"
#include "thread"
#include "Ghost.h"

class GUI::Game {
    int screenWidth;
    int screenHeight;
    std::shared_ptr<Model::World> world;
    std::shared_ptr<GUI::Camera> camera;
    std::shared_ptr<StateManager> stateManager;
public:
    Game();

    virtual ~Game();

    static direction getDirection();

    static key getInput();

    [[nodiscard]] const std::shared_ptr<Model::World> &getWorld() const;

    [[nodiscard]] const std::shared_ptr<GUI::Camera> &getCamera() const;

    [[nodiscard]] const std::shared_ptr<GUI::StateManager> &getStateManager() const;

    [[nodiscard]] int getScreenWidth() const;

    [[nodiscard]] int getScreenHeight() const;
    /*
     * Draws the current lives on the screen
     */
    void drawLives() const;

    /*
     * Draws the scoreBoard
     */
    static void drawScoreboard() ;

    /*
     * Gets the current mouse position
     */
    static sf::Vector2i getMousePosition();

    /*
     * Draws the startbutton
     */
    static void drawStartButton();

};


#endif //PAC_MAN_GAME_H
