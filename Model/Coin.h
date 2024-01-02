//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_COIN_H
#define PAC_MAN_COIN_H
#include "Collectable.h"
#include "Observer.h"

class Model::Coin: public Model::Collectable{
public:
    Coin(int row, int col);

    void update(const double &seconds) override;
};


#endif //PAC_MAN_COIN_H
