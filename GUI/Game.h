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
using namespace std;

class Game {
    int width;
    int height;
    EntityView* viewMap[11][20];
    vector<EntityView*> viewEntities;
    ConcreteFactory* factory;
    World* world;
    Stopwatch *stopwatch;

public:
    Game(const int &width, const int &height);

    virtual ~Game();

    void generateMap();

    static string getDirection();

    [[nodiscard]] pair<int, int> cameraToPixels(double xCamera, double yCamera) const;

    [[nodiscard]] int getWidth() const;

    void setWidth(int wd);

    [[nodiscard]] int getHeight() const;

    void setHeight(int hg);

    [[nodiscard]] World *getWorld() const;

    void setWorld(World *sWorld);

    void setViewItem(EntityView* entity, const int &row, const int &col);



};


#endif //PAC_MAN_GAME_H
