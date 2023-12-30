//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_COLLECTABLE_H
#define PAC_MAN_COLLECTABLE_H
#include "EntityModel.h"
#include "Observer.h"

class Model::Collectable: public Model::EntityModel{
    int value;
    bool consumed;
public:
    Collectable(int row, int col);

    void update(const double &seconds) override;

    [[nodiscard]] int getValue() const;

    void setValue(int val);

    [[nodiscard]] bool isConsumed() const;

    void consume();

    void restart();


};


#endif //PAC_MAN_COLLECTABLE_H
