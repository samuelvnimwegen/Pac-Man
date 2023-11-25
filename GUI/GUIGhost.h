//
// Created by Samuel on 21/11/2023.
//

#ifndef PAC_MAN_GUIGHOST_H
#define PAC_MAN_GUIGHOST_H
#include "EntityView.h"

class GUI::GUIGhost: public GUI::EntityView{
    int textureNr;
    int spriteX;
    color ghostColor;
public:
    explicit GUIGhost(color ghostColor);

    sf::Sprite getSprite() override;
};


#endif //PAC_MAN_GUIGHOST_H
