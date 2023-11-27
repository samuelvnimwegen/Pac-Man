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
    direction currentDirection;
    bool hasMoved;
public:
    explicit GUIPacMan();

    ~GUIPacMan() override;

    void move();

    void updateTextureNr();

    sf::Sprite getSprite() override;

    int getTextureNr() const;

    void setTextureNr(int nr);

    direction getDirection() const;

    void setDirection(direction direction);

    direction getCurrentDirection() const;

    void setCurrentDirection(direction direction);

    bool isHasMoved() const;

    void setHasMoved(bool moved);
};


#endif //PAC_MAN_GUIPACMAN_H
