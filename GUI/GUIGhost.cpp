//
// Created by Samuel on 21/11/2023.
//

#include "GUIGhost.h"



sf::Sprite GUI::GUIGhost::getSprite() {
    sf::Sprite sprite;

    sprite = sf::Sprite(this->getTexture(), sf::IntRect(spriteX, 0, 40, 40));


    return sprite;
}

GUI::GUIGhost::GUIGhost(Model::Ghost* ghost) : GUI::EntityView(ghost) {
    this->subject = ghost;
    textureNr = 0;
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
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
    Camera* camera = Camera::instance();
    xSpeed = camera->getXSpeed() * 0.5;
    ySpeed = camera->getYSpeed() * 0.5;
    subject = ghost;
}

void GUI::GUIGhost::move(const int &ticks) {
    Camera* camera = Camera::instance();
    this->getSubject()->changeDirection();
    if (this->getSubject()->getCurrentDirection() == up){
        double yCoord = this->getCameraY();
        yCoord -= ticks * this->getYSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getSubject()->getNextDirection() == direction::right and this->getSubject()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() + 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord();
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
        else if (this->getSubject()->getNextDirection() == direction::left and this->getSubject()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord();
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
        else if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() - 1, this->getSubject()->getCol()) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() - 1, this->getSubject()->getCol())->getTag() == "Wall"){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord();
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow() - 1, this->getSubject()->getCol()).getYCoord() - yCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord() - yCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol()) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol())->getTag() == "PacMan"){
                this->getSubject()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getRow() - 1, this->getSubject()->getCol())){
                this->setCameraY(yCoord);
                auto tempItem = this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() - 1, this->getSubject()->getCol());
                this->getSubject()->getWorld()->setItem(tempItem, this->getSubject()->getRow(), this->getSubject()->getCol());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getRow() - 1, this->getSubject()->getCol());
                this->getSubject()->setRow(this->getSubject()->getRow() - 1);
            }
        }else{
            this->setCameraY(yCoord);
        }
    }
    else if (this->getSubject()->getCurrentDirection() == direction::down){
        double yCoord = this->getCameraY();
        yCoord += ticks * this->getYSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getSubject()->getNextDirection() == direction::right and this->getSubject()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() + 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord();
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
        else if (this->getSubject()->getNextDirection() == direction::left and this->getSubject()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord();
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
        else if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol()) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol())->getTag() == "Wall"){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord();
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow() + 1, this->getSubject()->getCol()).getYCoord() - yCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord() - yCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol()) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol())->getTag() == "PacMan"){
                this->getSubject()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getRow() + 1, this->getSubject()->getCol())){
                this->setCameraY(yCoord);
                auto tempItem = this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol());
                this->getSubject()->getWorld()->setItem(tempItem, this->getSubject()->getRow(), this->getSubject()->getCol());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getRow() + 1, this->getSubject()->getCol());
                this->getSubject()->setRow(this->getSubject()->getRow() + 1);
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
        if (this->getSubject()->getNextDirection() == direction::up and this->getSubject()->canMove(this->getSubject()->getRow() - 1, this->getSubject()->getCol())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
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
        else if (this->getSubject()->getNextDirection() == direction::down and this->getSubject()->canMove(this->getSubject()->getRow() + 1, this->getSubject()->getCol())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
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
        else if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() + 1) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() + 1)->getTag() == "Wall"){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol() + 1).getXCoord() - xCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord() - xCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() + 1) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() + 1)->getTag() == "PacMan"){
                this->getSubject()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() + 1)){
                this->setCameraX(xCoord);
                auto tempItem = this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() + 1);
                this->getSubject()->getWorld()->setItem(tempItem, this->getSubject()->getRow(), this->getSubject()->getCol());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getRow(), this->getSubject()->getCol() + 1);
                this->getSubject()->setCol(this->getSubject()->getCol() + 1);
            }
        }else{
            this->setCameraX(xCoord);
        }
    }
    else if (this->getSubject()->getCurrentDirection() == direction::left){
        double xCoord = this->getCameraX();
        xCoord -= ticks * this->getXSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getSubject()->getNextDirection() == direction::up and this->getSubject()->canMove(this->getSubject()->getRow() - 1, this->getSubject()->getCol())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
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
        else if (this->getSubject()->getNextDirection() == direction::down and this->getSubject()->canMove(this->getSubject()->getRow() + 1, this->getSubject()->getCol())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
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
        else if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)->getTag() == "Wall"){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol() - 1).getXCoord() - xCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord() - xCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)->getTag() == "PacMan"){
                this->getSubject()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)){
                this->setCameraX(xCoord);
                auto tempItem = this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1);
                this->getSubject()->getWorld()->setItem(tempItem, this->getSubject()->getRow(), this->getSubject()->getCol());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getRow(), this->getSubject()->getCol() - 1);
                this->getSubject()->setCol(this->getSubject()->getCol() - 1);
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

Model::Ghost *GUI::GUIGhost::getSubject() const {
    return subject;
}

void GUI::GUIGhost::setSubject(Model::Ghost *sub) {
    GUIGhost::subject = sub;
}


