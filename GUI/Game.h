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
    int width;
    int height;
    shared_ptr<Model::World> world;
    shared_ptr<GUI::Camera> camera;
    shared_ptr<StateManager> stateManager;
public:
    Game(const int &width, const int &height);

    virtual ~Game();

    static direction getDirection();

    static std::string getInput();

    [[nodiscard]] pair<int, int> cameraToPixels(double xCamera, double yCamera) const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] const shared_ptr<Model::World> &getWorld() const;

    [[nodiscard]] const shared_ptr<GUI::Camera> &getCamera() const;

    [[nodiscard]] const shared_ptr<GUI::StateManager> &getStateManager() const;

};


#endif //PAC_MAN_GAME_H
