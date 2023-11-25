//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_GUIPACMAN_H
#include "EntityView.h"
#include "iostream"

class GUI::GUIPacMan: public GUI::EntityView{
    Model::PacMan* pacMan;
    int textureNr;
public:
    explicit GUIPacMan(Model::PacMan *pacMan);

    ~GUIPacMan() override;

    void updateTextureNr();

    sf::Sprite getSprite() override;

    int getTextureNr() const;

    void setTextureNr(int nr);

    Model::PacMan *getPacMan() const;

    void setPacMan(Model::PacMan *pMan);
};


#endif //PAC_MAN_GUIPACMAN_H
