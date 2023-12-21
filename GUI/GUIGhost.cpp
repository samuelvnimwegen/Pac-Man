//
// Created by Samuel on 21/11/2023.
//

#include "GUIGhost.h"

#include <utility>





GUI::GUIGhost::GUIGhost(const std::shared_ptr<Model::Ghost>& ghost, std::weak_ptr<sf::RenderWindow> win) : GUI::EntityView(ghost, std::move(win)) {
    subject = ghost;
    textureNr = 0;
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Sprites.png");
    this->setTexture(texture);
    color ghostColor = this->getSubject()->getColor();
    if (ghostColor == color::red){
        spriteX = 0;
    }else if (ghostColor == color::pink){
        spriteX = 50;
    }else if (ghostColor == color::blue){
        spriteX = 100;
    }else {
        spriteX = 150;
    }
    auto camera = Camera::instance();
    xSpeed = camera->getXSpeed() * 0.5;
    ySpeed = camera->getYSpeed() * 0.5;
    subject = ghost;
}

void GUI::GUIGhost::move(const int &ticks) {
    auto camera = Camera::instance();
    this->getSubject()->changeDirection();
    if (this->getSubject()->getCurrentDirection() == up){
        double yCoord = this->getCameraY();
        yCoord -= ticks * this->getYSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getSubject()->getNextDirection() == direction::right and this->getSubject()->canMove(
                this->getSubject()->getY(), this->getSubject()->getX() + 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getYCoord();
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() + this->getXSpeed());
                this->getSubject()->setCurrentDirection(direction::right);
                this->getSubject()->setNextDirection(direction::none);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

            // Als volgende direction naar links is en hij kan naar links:
        else if (this->getSubject()->getNextDirection() == direction::left and this->getSubject()->canMove(
                this->getSubject()->getY(), this->getSubject()->getX() - 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getYCoord();
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() - this->getXSpeed());
                this->getSubject()->setCurrentDirection(direction::left);
                this->getSubject()->setNextDirection(direction::none);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

            // Als de volgende tile een muur is:
        else if (this->getSubject()->getWorld()->getItem(this->getSubject()->getY() - 1, this->getSubject()->getX()) != nullptr and this->getSubject()->getWorld()->getItem(
                this->getSubject()->getY() - 1, this->getSubject()->getX())->getTag() == "Wall"){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getYCoord();
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getY() - 1, this->getSubject()->getX()).getYCoord() - yCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getYCoord() - yCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getY() + 1, this->getSubject()->getX()) != nullptr and this->getSubject()->getWorld()->getItem(
                    this->getSubject()->getY() + 1, this->getSubject()->getX())->getTag() == "PacMan"){
                this->getSubject()->getWorld()->restart();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getY() - 1, this->getSubject()->getX())){
                this->setCameraY(yCoord);
                auto tempItem = this->getSubject()->getWorld()->getItem(this->getSubject()->getY() - 1,
                                                                        this->getSubject()->getX());
                this->getSubject()->getWorld()->setItem(tempItem, this->getSubject()->getY(), this->getSubject()->getX());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getY() - 1,
                                                        this->getSubject()->getX());
                this->getSubject()->setY(this->getSubject()->getY() - 1);
            }
        }else{
            this->setCameraY(yCoord);
        }
    }
    else if (this->getSubject()->getCurrentDirection() == direction::down){
        double yCoord = this->getCameraY();
        yCoord += ticks * this->getYSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getSubject()->getNextDirection() == direction::right and this->getSubject()->canMove(
                this->getSubject()->getY(), this->getSubject()->getX() + 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getYCoord();
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() + this->getXSpeed());
                this->getSubject()->setCurrentDirection(direction::right);
                this->getSubject()->setNextDirection(direction::none);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Als volgende direction naar links is en hij kan naar links:
        else if (this->getSubject()->getNextDirection() == direction::left and this->getSubject()->canMove(
                this->getSubject()->getY(), this->getSubject()->getX() - 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getYCoord();
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() - this->getXSpeed());
                this->getSubject()->setCurrentDirection(direction::left);
                this->getSubject()->setNextDirection(direction::none);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getSubject()->getWorld()->getItem(this->getSubject()->getY() + 1, this->getSubject()->getX()) != nullptr and this->getSubject()->getWorld()->getItem(
                this->getSubject()->getY() + 1, this->getSubject()->getX())->getTag() == "Wall"){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getYCoord();
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getY() + 1, this->getSubject()->getX()).getYCoord() - yCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getYCoord() - yCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getY() + 1, this->getSubject()->getX()) != nullptr and this->getSubject()->getWorld()->getItem(
                    this->getSubject()->getY() + 1, this->getSubject()->getX())->getTag() == "PacMan"){
                this->getSubject()->getWorld()->restart();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getY() + 1, this->getSubject()->getX())){
                this->setCameraY(yCoord);
                auto tempItem = this->getSubject()->getWorld()->getItem(this->getSubject()->getY() + 1,
                                                                        this->getSubject()->getX());
                this->getSubject()->getWorld()->setItem(tempItem, this->getSubject()->getY(), this->getSubject()->getX());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getY() + 1,
                                                        this->getSubject()->getX());
                this->getSubject()->setY(this->getSubject()->getY() + 1);
            }
        }
        else{
            this->setCameraY(yCoord);
        }
    }
    else if (this->getSubject()->getCurrentDirection() == direction::right){
        double xCoord = this->getCameraX();
        xCoord += ticks * this->getXSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getSubject()->getNextDirection() == direction::up and this->getSubject()->canMove(
                this->getSubject()->getY() - 1, this->getSubject()->getX())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getXCoord();
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() - this->getYSpeed());
                this->getSubject()->setCurrentDirection(direction::up);
                this->getSubject()->setNextDirection(direction::none);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
        else if (this->getSubject()->getNextDirection() == direction::down and this->getSubject()->canMove(
                this->getSubject()->getY() + 1, this->getSubject()->getX())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getXCoord();
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() + this->getYSpeed());
                this->getSubject()->setCurrentDirection(direction::down);
                this->getSubject()->setNextDirection(direction::none);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getSubject()->getWorld()->getItem(this->getSubject()->getY(), this->getSubject()->getX() + 1) != nullptr and this->getSubject()->getWorld()->getItem(
                this->getSubject()->getY(), this->getSubject()->getX() + 1)->getTag() == "Wall"){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getXCoord();
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX() + 1).getXCoord() - xCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getXCoord() - xCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getY(), this->getSubject()->getX() + 1) != nullptr and this->getSubject()->getWorld()->getItem(
                    this->getSubject()->getY(), this->getSubject()->getX() + 1)->getTag() == "PacMan"){
                this->getSubject()->getWorld()->restart();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getY(), this->getSubject()->getX() + 1)){
                this->setCameraX(xCoord);
                auto tempItem = this->getSubject()->getWorld()->getItem(this->getSubject()->getY(),
                                                                        this->getSubject()->getX() + 1);
                this->getSubject()->getWorld()->setItem(tempItem, this->getSubject()->getY(), this->getSubject()->getX());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getY(),
                                                        this->getSubject()->getX() + 1);
                this->getSubject()->setX(this->getSubject()->getX() + 1);
            }
        }else{
            this->setCameraX(xCoord);
        }
    }
    else if (this->getSubject()->getCurrentDirection() == direction::left){
        double xCoord = this->getCameraX();
        xCoord -= ticks * this->getXSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getSubject()->getNextDirection() == direction::up and this->getSubject()->canMove(
                this->getSubject()->getY() - 1, this->getSubject()->getX())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getXCoord();
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() - this->getYSpeed());
                this->getSubject()->setCurrentDirection(direction::up);
                this->getSubject()->setNextDirection(direction::none);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
        else if (this->getSubject()->getNextDirection() == direction::down and this->getSubject()->canMove(
                this->getSubject()->getY() + 1, this->getSubject()->getX())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getXCoord();
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() + this->getYSpeed());
                this->getSubject()->setCurrentDirection(direction::down);
                this->getSubject()->setNextDirection(direction::none);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getSubject()->getWorld()->getItem(this->getSubject()->getY(), this->getSubject()->getX() - 1) != nullptr and this->getSubject()->getWorld()->getItem(
                this->getSubject()->getY(), this->getSubject()->getX() - 1)->getTag() == "Wall"){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getXCoord();
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX() - 1).getXCoord() - xCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX()).getXCoord() - xCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getY(), this->getSubject()->getX() - 1) != nullptr and this->getSubject()->getWorld()->getItem(
                    this->getSubject()->getY(), this->getSubject()->getX() - 1)->getTag() == "PacMan"){
                this->getSubject()->getWorld()->restart();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getY(), this->getSubject()->getX() - 1)){
                this->setCameraX(xCoord);
                auto tempItem = this->getSubject()->getWorld()->getItem(this->getSubject()->getY(),
                                                                        this->getSubject()->getX() - 1);
                this->getSubject()->getWorld()->setItem(tempItem, this->getSubject()->getY(), this->getSubject()->getX());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getY(),
                                                        this->getSubject()->getX() - 1);
                this->getSubject()->setX(this->getSubject()->getX() - 1);
            }
        }else{
            this->setCameraX(xCoord);
        }
    }
    else{
        assert(false);
    }
}

double GUI::GUIGhost::getYSpeed() const {
    return ySpeed;
}

void GUI::GUIGhost::setYSpeed(double speed) {
    GUIGhost::ySpeed = speed;
}

double GUI::GUIGhost::getXSpeed() const {
    return xSpeed;
}

void GUI::GUIGhost::setXSpeed(double speed) {
    GUIGhost::xSpeed = speed;
}

std::shared_ptr<Model::Ghost> GUI::GUIGhost::getSubject(){
    return subject;
}

void GUI::GUIGhost::update(const int &ticks) {
    this->updateSprite();
    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());
    auto sprite1 = this->getSprite();
    sprite1->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite1);
    EntityView::update(ticks);
}

void GUI::GUIGhost::updateSprite() {
    sf::Sprite sprite;
    sprite = sf::Sprite(*this->getTexture(), sf::IntRect(spriteX, 0, 40, 40));
    this->setSprite(std::make_shared<sf::Sprite>(sprite));
}



