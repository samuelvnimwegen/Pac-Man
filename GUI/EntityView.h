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
    sf::Sprite sprite;
public:
    virtual ~EntityView();

    const sf::Texture &getTexture() const;

    void removeSprite();

    void setTexture(const sf::Texture &entityTexture);

     int getCol() const;

    void setCol(int c);

    int getRow() const;

    void setRow(int r);

    explicit EntityView();

    virtual sf::Sprite getSprite();

    void setSprite(const sf::Sprite &entitySprite);
};


#endif //PAC_MAN_ENTITYVIEW_H
