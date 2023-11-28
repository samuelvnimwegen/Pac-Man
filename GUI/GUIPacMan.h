//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_GUIPACMAN_H
#include "EntityView.h"
#include "iostream"

class GUI::GUIPacMan: public GUI::EntityView{
    Model::PacMan* subject;
    int textureNr;
    double xSpeed;
    double ySpeed;
public:
    explicit GUIPacMan(Model::PacMan* subject);

    ~GUIPacMan() override;

    void move(const int &ticks) override;

    void updateTextureNr();

    sf::Sprite getSprite() override;

    int getTextureNr() const;

    void setTextureNr(int nr);

    Model::PacMan *getSubject() const;

    double getXSpeed() const;

    double getYSpeed() const;
};


#endif //PAC_MAN_GUIPACMAN_H
