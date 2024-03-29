//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYVIEW_H
#define PAC_MAN_ENTITYVIEW_H
#include "../Model/Observer.h"
#include "../Model/World.h"
#include "SFML/Graphics.hpp"
#include "Window.h"

class GUI::EntityView: public Model::Observer{
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;
    std::weak_ptr<Model::EntityModel> subject;
public:
    explicit EntityView(const std::shared_ptr<Model::EntityModel>& subject);

    void collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) override;

    virtual ~EntityView();

    void levelHalt() override;

    void pacManDied() override;

    void ghostEaten() override;

    void restartGame() override;

    void nextLevel() override;

    //////////////////////////////
    // Getters en setters
    //////////////////////////////

    [[nodiscard]] static std::pair<int, int> cameraToPixels(double xCamera, double yCamera);

    [[nodiscard]] const std::shared_ptr<sf::Texture> &getTexture() const;

    void setTexture(const std::shared_ptr<sf::Texture> &sharedPtr);

    virtual std::shared_ptr<sf::Sprite> getSprite();

    void setSprite(const std::shared_ptr<sf::Sprite> &sharedPtr);

    void update(const double &ticks) override;

    [[nodiscard]] virtual std::shared_ptr<Model::EntityModel> getSubject() const;
};


#endif //PAC_MAN_ENTITYVIEW_H
