//
// Created by Samuel on 20/11/2023.
//

#ifndef PAC_MAN_GUICOIN_H
#define PAC_MAN_GUICOIN_H
#include "EntityView.h"

class GUI::Coin: public GUI::EntityView{
    std::weak_ptr<Model::Coin> subject;
public:
    explicit Coin(const std::shared_ptr<Model::Coin> &coin);

    void update(const double &ticks) override;

    [[nodiscard]] std::shared_ptr<Model::Coin> getSubject();

    ~Coin() override;
};


#endif //PAC_MAN_GUICOIN_H
