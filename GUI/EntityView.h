//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYVIEW_H
#define PAC_MAN_ENTITYVIEW_H
#include "../Observer.h"
#include "SFML/Graphics.hpp"

class EntityView: public Observer{
    int col;
    int row;
    sf::Texture texture;
public:
    const sf::Texture &getTexture() const;

    void setTexture(const sf::Texture &texture);

public:
    int getCol() const;

    void setCol(int c);

    int getRow() const;

    void setRow(int r);

    explicit EntityView(Subject *subject);

    virtual sf::Sprite getSprite();
};


#endif //PAC_MAN_ENTITYVIEW_H
