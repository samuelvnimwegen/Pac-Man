//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_GUIPACMAN_H
#include "EntityView.h"

class GUIPacMan: public EntityView{
    PacMan* subject;
public:
    explicit GUIPacMan(PacMan *subject);

    sf::Sprite getSprite() override;

    Subject * getSubject() const override;
};


#endif //PAC_MAN_GUIPACMAN_H
