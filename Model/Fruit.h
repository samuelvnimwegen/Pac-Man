//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_FRUIT_H
#define PAC_MAN_FRUIT_H
#include "Collectable.h"

class Model::Fruit: public Model::Collectable{
public:
    Fruit(int row, int col);
};


#endif //PAC_MAN_FRUIT_H
