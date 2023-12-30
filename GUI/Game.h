//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GAME_H
#define PAC_MAN_GAME_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "iostream"
#include "vector"
#include "../Observer.h"
#include "cassert"
#include "EntityView.h"
#include "GUIWall.h"
#include "ConcreteFactory.h"
#include "../Camera.h"
#include "GUIPacMan.h"
#include "../Stopwatch.h"
#include "GUICoin.h"
#include "StateManager.h"
#include "chrono"
#include "thread"
#include "GUIGhost.h"

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

    [[nodiscard]] std::pair<int, int> cameraToPixels(double xCamera, double yCamera) const;

    [[nodiscard]] const std::shared_ptr<Model::World> &getWorld() const;

    [[nodiscard]] const std::shared_ptr<GUI::Camera> &getCamera() const;

    [[nodiscard]] const std::shared_ptr<GUI::StateManager> &getStateManager() const;

    [[nodiscard]] int getScreenWidth() const;

    [[nodiscard]] int getScreenHeight() const;

};


#endif //PAC_MAN_GAME_H
