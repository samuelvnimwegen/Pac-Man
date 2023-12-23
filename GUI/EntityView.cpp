//
// Created by Samuel on 16/11/2023.
//

#include "EntityView.h"

#include <utility>




GUI::EntityView::~EntityView() = default;




GUI::EntityView::EntityView(const std::shared_ptr<Model::EntityModel>& subject, std::weak_ptr<sf::RenderWindow> win) : subject(subject), window(std::move(win)) {}

std::shared_ptr<Model::EntityModel> GUI::EntityView::getSubject() const {
    return subject.lock();
}

void GUI::EntityView::update(const int &ticks) {
    if (this->getWindow().lock()){
        this->getWindow().lock()->draw(*this->getSprite());
    }
}

std::pair<int, int> GUI::EntityView::cameraToPixels(double xCamera, double yCamera) const {
    int x, y = 0;
    if (this->getWindow().lock()){
        x = int((xCamera + 1) / 2 * float(this->getWindow().lock()->getSize().x));
        y = int((yCamera + 1) / 2 * float(this->getWindow().lock()->getSize().y));
    }
    return std::make_pair(x, y);
}

const std::weak_ptr<sf::RenderWindow> &GUI::EntityView::getWindow() const {
    return window;
}

const std::shared_ptr<sf::Texture> &GUI::EntityView::getTexture() const {
    return texture;
}

void GUI::EntityView::setTexture(const std::shared_ptr<sf::Texture> &sharedPtr) {
    EntityView::texture = sharedPtr;
}

std::shared_ptr<sf::Sprite> GUI::EntityView::getSprite() {
    return sprite;
}

void GUI::EntityView::setSprite(const std::shared_ptr<sf::Sprite> &sharedPtr) {
    EntityView::sprite = sharedPtr;
}


