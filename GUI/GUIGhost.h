//
// Created by Samuel on 21/11/2023.
//

#ifndef PAC_MAN_GUIGHOST_H
#define PAC_MAN_GUIGHOST_H
#include "EntityView.h"

class GUI::GUIGhost: public GUI::EntityView{
    std::weak_ptr<Model::Ghost> subject;
    int textureNr;
    int fearedTextureNr;
    double fearedUpdateTime;
    int spriteX;
    std::shared_ptr<sf::Texture> scoreTexture;
public:
    explicit GUIGhost(const std::shared_ptr<Model::Ghost> &ghost, color ghostColor);

    void update(const double &seconds) override;

    void updateSprite();

    std::shared_ptr<Model::Ghost> getSubject();

    [[nodiscard]] const std::shared_ptr<sf::Texture> &getScoreTexture() const;

    [[nodiscard]] int getTextureNr() const;

    void setTextureNr(int nr);

    [[nodiscard]] int getSpriteX() const;

    [[nodiscard]] int getFearedTextureNr() const;

    void setFearedTextureNr(int nr);

    [[nodiscard]] double getFearedUpdateTime() const;

    void setFearedUpdateTime(double updateTime);

    void collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) override;
};


#endif //PAC_MAN_GUIGHOST_H
