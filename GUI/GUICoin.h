//
// Created by Samuel on 20/11/2023.
//

#ifndef PAC_MAN_GUICOIN_H
#define PAC_MAN_GUICOIN_H
#include "EntityView.h"

class GUI::GUICoin: public GUI::EntityView{
    std::weak_ptr<Model::Coin> subject;
public:
    explicit GUICoin(const std::shared_ptr<Model::Coin> &coin);

    void update(const double &ticks) override;

    [[nodiscard]] std::shared_ptr<Model::Coin> getSubject();

    ~GUICoin() override;
};


#endif //PAC_MAN_GUICOIN_H
