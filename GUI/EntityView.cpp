//
// Created by Samuel on 16/11/2023.
//

#include "EntityView.h"
#include <utility>
#include "Camera.h"



GUI::EntityView::~EntityView() = default;




GUI::EntityView::EntityView(const std::shared_ptr<Model::EntityModel>& subject) : subject(subject){}

std::shared_ptr<Model::EntityModel> GUI::EntityView::getSubject() const {
    return subject.lock();
}

void GUI::EntityView::update(const double &ticks) {
    Window::instance()->getWindow()->draw(*this->getSprite());
}

std::pair<int, int> GUI::EntityView::cameraToPixels(double xCamera, double yCamera) {
    int x, y = 0;
    // Factor .99 is om de kleine gaps tussen sprites te elimineren.
    x = int((xCamera + 1) / 2 * float(Camera::instance()->getScreenWidth()) * 0.99);
    y = int((yCamera + 1) / 2 * float(Camera::instance()->getScreenHeight()) * 0.99);
    return std::make_pair(x, y);
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

void GUI::EntityView::collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) {}

void GUI::EntityView::levelHalt() {

}

void GUI::EntityView::pacManDied() {

}

void GUI::EntityView::ghostEaten() {

}

void GUI::EntityView::restartGame() {

}

void GUI::EntityView::nextLevel() {

}


