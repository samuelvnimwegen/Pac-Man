//
// Created by Samuel on 20/11/2023.
//

#ifndef PAC_MAN_GUICOIN_H
#define PAC_MAN_GUICOIN_H
#include "EntityView.h"

class GUI::GUICoin: public GUI::EntityView{
    Coin* subject;
public:
    explicit GUICoin(Coin *subject);

    ~GUICoin() override;

    Coin* getSubject() const override;
};


#endif //PAC_MAN_GUICOIN_H
