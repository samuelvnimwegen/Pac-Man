//
// Created by Samuel on 21/11/2023.
//

#ifndef PAC_MAN_GUIGHOST_H
#define PAC_MAN_GUIGHOST_H
#include "EntityView.h"
#include "SFML/Audio.hpp"
class GUI::Ghost: public GUI::EntityView{
    std::weak_ptr<Model::Ghost> subject;
    double walkLastUpdated;
    int textureNr;
    int fearedTextureNr;
    double fearedUpdateTime; // Laatste tijd waarop
    int spriteX; // X-coordinate op sprite-sheet, dit is voor de kleur
    std::shared_ptr<sf::Texture> scoreTexture;
    std::unique_ptr<sf::SoundBuffer> ghostEatenSoundBuffer;
    std::unique_ptr<sf::Sound> ghostEatenSound;
public:
    explicit Ghost(const std::shared_ptr<Model::Ghost> &ghost, color ghostColor);

    void update(const double &seconds) override;

    void updateSprite();

    void ghostEaten() override;

    /////////////////////////////////
    // Getters and setters
    /////////////////////////////////

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

    [[nodiscard]] double getWalkLastUpdated() const;

    void setWalkLastUpdated(double lastUpdated);
};


#endif //PAC_MAN_GUIGHOST_H
