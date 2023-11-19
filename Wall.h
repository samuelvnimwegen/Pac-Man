//
// Created by Samuel on 16/11/2023.
//
#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_PACMAN_H
#include "EntityModel.h"

using namespace std;

class Wall: public EntityModel{
public:
    Wall(int row, int col);
};


#endif //PAC_MAN_GUIWALL_H
