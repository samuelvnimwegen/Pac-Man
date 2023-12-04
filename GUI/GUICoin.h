//
// Created by Samuel on 20/11/2023.
//

#ifndef PAC_MAN_GUICOIN_H
#define PAC_MAN_GUICOIN_H
#include "EntityView.h"

class GUI::GUICoin: public GUI::EntityView{
    Model::Coin* subject;
public:
    explicit GUICoin(Model::Coin *coin);

    ~GUICoin() override;
};


#endif //PAC_MAN_GUICOIN_H
