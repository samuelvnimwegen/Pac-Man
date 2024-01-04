//
// Created by Samuel on 03/01/2024.
//

#ifndef PAC_MAN_GUIESCAPEWALL_H
#define PAC_MAN_GUIESCAPEWALL_H
#include "EntityView.h"

class GUI::EscapeWall: public GUI::EntityView{
public:
    explicit EscapeWall(const std::shared_ptr<Model::EscapeWall> &sub);

    void collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) override;

    void update(const double &ticks) override;

    [[nodiscard]] std::shared_ptr<Model::EntityModel> getSubject() const override;

    std::shared_ptr<sf::Sprite> getSprite() override;
};


#endif //PAC_MAN_GUIESCAPEWALL_H
