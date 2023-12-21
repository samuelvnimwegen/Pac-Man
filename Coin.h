//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_COIN_H
#define PAC_MAN_COIN_H
#include "Collectable.h"
#include "Observer.h"

class Model::Coin: public Model::Collectable{
    bool consumed;
public:
    Coin(int row, int col);

    [[nodiscard]] bool isConsumed1() const;

    void setConsumed(bool cons);

    void update(const int &ticks) override;
};


#endif //PAC_MAN_COIN_H
