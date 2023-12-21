//
// Created by Samuel on 20/11/2023.
//

#ifndef PAC_MAN_GUICOIN_H
#define PAC_MAN_GUICOIN_H
#include "EntityView.h"

class GUI::GUICoin: public GUI::EntityView{
public:
    explicit GUICoin(const std::shared_ptr<Model::Coin>& coin, std::weak_ptr<sf::RenderWindow> win);

    void update(const int &ticks) override;

    ~GUICoin() override;
};


#endif //PAC_MAN_GUICOIN_H
