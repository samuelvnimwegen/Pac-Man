//
// Created by Samuel on 21/11/2023.
//

#ifndef PAC_MAN_GUIGHOST_H
#define PAC_MAN_GUIGHOST_H
#include "EntityView.h"

class GUI::GUIGhost: public GUI::EntityView{
    int textureNr;
    int spriteX;
    double ySpeed;
    double xSpeed;
    Model::Ghost* subject;
public:
    explicit GUIGhost(Model::Ghost* ghost);

    void move(const int &ticks) override;

    sf::Sprite getSprite() override;

    double getYSpeed() const;

    void setYSpeed(double speed);

    double getXSpeed() const;

    void setXSpeed(double speed);

    Model::Ghost *getSubject() const;

    void setSubject(Model::Ghost *sub);
};


#endif //PAC_MAN_GUIGHOST_H
