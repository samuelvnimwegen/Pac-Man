//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_COLLECTABLE_H
#define PAC_MAN_COLLECTABLE_H
#include "EntityModel.h"

class Collectable: public EntityModel{
    int value;

public:
    Collectable(int row, int col);

    [[nodiscard]] int getValue() const;

    void setValue(int value);


};


#endif //PAC_MAN_COLLECTABLE_H
