//
// Created by Samuel on 16/11/2023.
//
#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_PACMAN_H
#include "EntityModel.h"
#include "Subject.h"
#include "Observer.h"

class Model::Wall: public Model::EntityModel{
public:
    Wall(int row, int col);

    void update(const int &ticks) override;
};


#endif //PAC_MAN_GUIWALL_H
