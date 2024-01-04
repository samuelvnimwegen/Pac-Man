//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_GUIPACMAN_H
#include "EntityView.h"
#include "iostream"
#include "SFML/Audio.hpp"

class GUI::GUIPacMan: public GUI::EntityView{
    std::weak_ptr<Model::PacMan> pacManModel;
    int textureNr;
    int deadTextureNr;
    std::unique_ptr<sf::SoundBuffer> chompSoundBuffer;
    std::unique_ptr<sf::Sound> chompSound;
    std::unique_ptr<sf::SoundBuffer> fruitSoundBuffer;
    std::unique_ptr<sf::Sound> fruitSound;
    std::unique_ptr<sf::SoundBuffer> frightenedSoundBuffer;
    std::unique_ptr<sf::Sound> frightenedSound;
    std::unique_ptr<sf::SoundBuffer> deathSoundBuffer;
    std::unique_ptr<sf::Sound> deathSound;
    std::unique_ptr<sf::SoundBuffer> ghostEatenSoundBuffer;
    std::unique_ptr<sf::Sound> ghostEatenSound;
    double lastCoinCollected;
public:
    explicit GUIPacMan(const std::shared_ptr<Model::PacMan> &subject);

    ~GUIPacMan() override;

    void update(const double &ticks) override;

    void levelHalt() override;

    void pacManDied() override;

    void updateTextureNr();

    void updateSprite();

    [[nodiscard]] int getTextureNr() const;

    void setTextureNr(int nr);

    [[nodiscard]] std::shared_ptr<Model::PacMan> getPacManModel() const;

    [[nodiscard]] int getDeadTextureNr() const;

    void setDeadTextureNr(int nr);

    void collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) override;

    [[nodiscard]] double getLastCoinCollected() const;

    void setLastCoinCollected(double lastCollected);
};


#endif //PAC_MAN_GUIPACMAN_H
