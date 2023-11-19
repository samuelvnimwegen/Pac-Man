//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_GUIPACMAN_H
#include "EntityView.h"

class GUIPacMan: public EntityView{
public:
    explicit GUIPacMan(Subject *subject);

    sf::Sprite getSprite() override;
};


#endif //PAC_MAN_GUIPACMAN_H
