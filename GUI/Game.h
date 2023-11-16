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
using namespace std;

class Game {
    int width;
    int height;
    Observer* observer;
    World* world;
    int pixelWidth;
    int pixelHeight;
public:
    Game(const int &width, const int &height);

    [[nodiscard]] int getWidth() const;

    void setWidth(int wd);

    [[nodiscard]] int getHeight() const;

    void setHeight(int hg);

    pair<int, int> calculatePixel(const int &row, const int &column);

    [[nodiscard]] World *getWorld() const;

    void setWorld(World *world);
};


#endif //PAC_MAN_GAME_H
