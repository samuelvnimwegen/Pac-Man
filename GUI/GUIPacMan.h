//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_GUIPACMAN_H
#include "EntityView.h"
#include "iostream"

class GUI::GUIPacMan: public GUI::EntityView{
    std::weak_ptr<Model::PacMan> pacManModel;
    int textureNr;
    double xSpeed;
    double ySpeed;
public:

    explicit GUIPacMan(const std::shared_ptr<Model::PacMan>& subject);

    ~GUIPacMan() override;

    void move(const int &ticks) override;

    void updateTextureNr();

    sf::Sprite getSprite() override;

    int getTextureNr() const;

    void setTextureNr(int nr);

    double getXSpeed() const;

    double getYSpeed() const;

    std::shared_ptr<Model::PacMan> getPacManModel() const;
};


#endif //PAC_MAN_GUIPACMAN_H
