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
    vector<EntityView*> viewEntities;
    Model::World* world;
    GUI::Camera* camera;
    StateManager* stateManager;
    vector<GUI::GUIGhost*> ghosts;
    vector<GUI::GUIWall*> walls;
    vector<GUI::GUICoin*> coins;
    GUI::GUIPacMan* pacMan;

public:
    Game(const int &width, const int &height);

    virtual ~Game();

    static direction getDirection();

    static std::string getInput();

    [[nodiscard]] pair<int, int> cameraToPixels(double xCamera, double yCamera) const;

    [[nodiscard]] int getWidth() const;

    void setWidth(int wd);

    [[nodiscard]] int getHeight() const;

    void setHeight(int hg);

    [[nodiscard]] Model::World *getWorld() const;

    void setWorld(Model::World *sWorld);

    [[nodiscard]] StateManager *getStateManager() const;

    void setStateManager(StateManager *state);

};


#endif //PAC_MAN_GAME_H
