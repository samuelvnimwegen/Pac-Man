//
// Created by Samuel on 21/11/2023.
//

#ifndef PAC_MAN_GUIGHOST_H
#define PAC_MAN_GUIGHOST_H
#include "EntityView.h"

class GUI::GUIGhost: public GUI::EntityView{
    std::weak_ptr<Model::Ghost> subject;
    int textureNr;
    int spriteX;
    std::shared_ptr<sf::Texture> scoreTexture;
public:
    explicit GUIGhost(const std::shared_ptr<Model::Ghost> &ghost, color ghostColor);

    void update(const double &seconds) override;

    void updateSprite();

    std::shared_ptr<Model::Ghost> getSubject();

    [[nodiscard]] const std::shared_ptr<sf::Texture> &getScoreTexture() const;
};


#endif //PAC_MAN_GUIGHOST_H
