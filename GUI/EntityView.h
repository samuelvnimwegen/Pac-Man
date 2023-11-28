//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYVIEW_H
#define PAC_MAN_ENTITYVIEW_H
#include "../Observer.h"
#include "../World.h"
#include "SFML/Graphics.hpp"

class GUI::EntityView: public Model::Observer{
    sf::Texture texture;
    sf::Sprite sprite;
    double cameraX;
    double cameraY;
public:
    virtual ~EntityView();

    const sf::Texture &getTexture() const;

    void removeSprite();

    void setTexture(const sf::Texture &entityTexture);

    explicit EntityView();

    sf::Sprite getSprite() override;

    void setSprite(const sf::Sprite &entitySprite);

    double getCameraX() const override;

    void setCameraX(double x) override;

    double getCameraY() const override;

    void setCameraY(double y) override;

    void move(const int &ticks) override;

};


#endif //PAC_MAN_ENTITYVIEW_H
