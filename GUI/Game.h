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
using namespace std;

class Game {
    int width;
    int height;
    EntityView* viewMap[11][20];
    vector<EntityView*> viewEntities;
    ConcreteFactory* factory;
    World* world;
    Stopwatch *stopwatch;
    StateManager* stateManager;
    vector<GUIGhost*> ghosts;
    vector<GUIWall*> walls;
    vector<GUICoin*> coins;
    GUIPacMan* pacMan;

public:
    Game(const int &width, const int &height);

    virtual ~Game();

    void generateMap();

    static string getDirection();

    static string getInput();

    [[nodiscard]] pair<int, int> cameraToPixels(double xCamera, double yCamera) const;

    [[nodiscard]] int getWidth() const;

    void setWidth(int wd);

    [[nodiscard]] int getHeight() const;

    void setHeight(int hg);

    [[nodiscard]] World *getWorld() const;

    void setWorld(World *sWorld);

    void setViewItem(EntityView* entity, const int &row, const int &col);

    [[nodiscard]] StateManager *getStateManager() const;

    void setStateManager(StateManager *state);

    [[nodiscard]] Stopwatch *getStopwatch() const;

    void setStopwatch(Stopwatch *newStopwatch);

    [[nodiscard]] const vector<GUIGhost *> &getGhosts() const;

    void setGhosts(const vector<GUIGhost *> &ghostVector);

    [[nodiscard]] const vector<GUIWall *> &getWalls() const;

    void setWalls(const vector<GUIWall *> &wallsVector);

    [[nodiscard]] const vector<GUICoin *> &getCoins() const;

    void setCoins(const vector<GUICoin *> &coinVector);

    [[nodiscard]] GUIPacMan *getPacMan() const;

    void setPacMan(GUIPacMan *guiPacMan);

    void addWall(GUIWall* wall);

    void addCoin(GUICoin* coin);

    void addGhost(GUIGhost* ghost);


};


#endif //PAC_MAN_GAME_H
