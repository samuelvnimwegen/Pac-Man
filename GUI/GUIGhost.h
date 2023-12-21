//
// Created by Samuel on 21/11/2023.
//

#ifndef PAC_MAN_GUIGHOST_H
#define PAC_MAN_GUIGHOST_H
#include "EntityView.h"

class GUI::GUIGhost: public GUI::EntityView{
    std::shared_ptr<Model::Ghost> subject;
    int textureNr;
    int spriteX;
    double ySpeed;
    double xSpeed;
public:
    explicit GUIGhost(const std::shared_ptr<Model::Ghost>& ghost, std::weak_ptr<sf::RenderWindow> win);

    void move(const int &ticks) override;

    void update(const int &ticks) override;

    void updateSprite();

    [[nodiscard]] double getYSpeed() const;

    void setYSpeed(double speed);

    [[nodiscard]] double getXSpeed() const;

    void setXSpeed(double speed);

    std::shared_ptr<Model::Ghost> getSubject();

};


#endif //PAC_MAN_GUIGHOST_H
