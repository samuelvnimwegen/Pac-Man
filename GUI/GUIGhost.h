//
// Created by Samuel on 21/11/2023.
//

#ifndef PAC_MAN_GUIGHOST_H
#define PAC_MAN_GUIGHOST_H
#include "EntityView.h"

class GUI::GUIGhost: public GUI::EntityView{
    std::weak_ptr<Model::Ghost> subject;
    int textureNr;
    int spriteX;
public:
    explicit GUIGhost(const std::shared_ptr<Model::Ghost>& ghost, std::weak_ptr<sf::RenderWindow> win);

    void update(const double &seconds) override;

    void updateSprite();

    std::shared_ptr<Model::Ghost> getSubject();
};


#endif //PAC_MAN_GUIGHOST_H
