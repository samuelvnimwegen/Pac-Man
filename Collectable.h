//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_COLLECTABLE_H
#define PAC_MAN_COLLECTABLE_H
#include "EntityModel.h"
#include "Observer.h"

class Model::Collectable: public Model::EntityModel{
    int value;

public:
    Collectable(int row, int col);

    void update(const int &ticks) override;

    [[nodiscard]] int getValue() const;

    void setValue(int val);


};


#endif //PAC_MAN_COLLECTABLE_H
