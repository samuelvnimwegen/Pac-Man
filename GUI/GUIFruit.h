//
// Created by Samuel on 28/12/2023.
//

#ifndef PAC_MAN_GUIFRUIT_H
#define PAC_MAN_GUIFRUIT_H
#include "EntityView.h"

class GUI::GUIFruit: public GUI::EntityView{
    std::weak_ptr<Model::Fruit> subject;
public:
    explicit GUIFruit(const std::shared_ptr<Model::Fruit> &subject);

    [[nodiscard]] std::shared_ptr<Model::Fruit> getSubject();

    void update(const double &ticks) override;
};


#endif //PAC_MAN_GUIFRUIT_H
