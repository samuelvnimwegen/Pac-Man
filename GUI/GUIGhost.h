//
// Created by Samuel on 21/11/2023.
//

#ifndef PAC_MAN_GUIGHOST_H
#define PAC_MAN_GUIGHOST_H
#include "EntityView.h"

class GUIGhost: public EntityView{
    Ghost* subject;
    int textureNr;
    int spriteX;
public:
    explicit GUIGhost(Ghost *subject);

    Ghost * getSubject() const override;

    sf::Sprite getSprite() override;
};


#endif //PAC_MAN_GUIGHOST_H
