//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYVIEW_H
#define PAC_MAN_ENTITYVIEW_H
#include "../Observer.h"
#include "../World.h"
#include "SFML/Graphics.hpp"

class GUI::EntityView: public Model::Observer{
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;
    std::weak_ptr<Model::EntityModel> subject;
    std::weak_ptr<sf::RenderWindow> window;
public:
    explicit EntityView(const std::shared_ptr<Model::EntityModel>& subject, std::weak_ptr<sf::RenderWindow> win);

    virtual ~EntityView();

    [[nodiscard]] const std::shared_ptr<sf::Texture> &getTexture() const;

    void setTexture(const std::shared_ptr<sf::Texture> &sharedPtr);

    virtual std::shared_ptr<sf::Sprite> getSprite();

    void setSprite(const std::shared_ptr<sf::Sprite> &sharedPtr);

    void update(const int &ticks) override;

    [[nodiscard]] virtual std::shared_ptr<Model::EntityModel> getSubject() const;

    [[nodiscard]] std::pair<int, int> cameraToPixels(double xCamera, double yCamera) const;

    [[nodiscard]] const std::weak_ptr<sf::RenderWindow> &getWindow() const;
};


#endif //PAC_MAN_ENTITYVIEW_H
