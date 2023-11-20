//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_GUIPACMAN_H
#include "EntityView.h"
#include "iostream"
using namespace std;
class GUIPacMan: public EntityView{
    PacMan* subject;
    int textureNr;
public:
    explicit GUIPacMan(PacMan *subject);

    void updateTextureNr();

    sf::Sprite getSprite() override;

    PacMan * getSubject() const override;

    int getTextureNr() const;

    void setTextureNr(int nr);
};


#endif //PAC_MAN_GUIPACMAN_H
