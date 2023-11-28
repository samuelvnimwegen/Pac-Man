//
// Created by Samuel on 16/11/2023.
//

#include "GUIPacMan.h"
using namespace std;


sf::Sprite GUI::GUIPacMan::getSprite() {
    sf::Sprite sprite;
    direction dir = this->getSubject()->getCurrentDirection();
    if (dir == direction::none){
        sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 1, 40, 40));
    }
    else if (dir == direction::right){
        if (this->getTextureNr() == 0){
           sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 51, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 101, 40, 40));
        }
    }
    else if (dir == direction::left){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 201, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 251, 40, 40));
        }
    }
    else if (dir == direction::up){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 351, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 401, 40, 40));
        }
    }
    else{
        assert(dir == direction::up);
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 501, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 551, 40, 40));
        }
    }
    if (this->getSubject()->isHasMoved()){
        this->updateTextureNr();
    }
    return sprite;
}

GUI::GUIPacMan::GUIPacMan(Model::PacMan* sub){
    textureNr = 0;
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    subject = sub;
    Camera* cam = Camera::instance();
    xSpeed = cam->getXSpeed();
    ySpeed = cam->getYSpeed();
}



int GUI::GUIPacMan::getTextureNr() const {
    return textureNr;
}

void GUI::GUIPacMan::setTextureNr(int nr) {
    GUIPacMan::textureNr = nr;
}

void GUI::GUIPacMan::updateTextureNr() {
    if (textureNr < 1){
        ++textureNr;
    }
    else{
        textureNr = 0;
    }
}


void GUI::GUIPacMan::move(const int &ticks) {
    Camera* camera = Camera::instance();
    this->getSubject()->setHasMoved(true);
    if (this->getSubject()->getCurrentDirection() == direction::up){
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
                this->getSubject()->setHasMoved(false);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow() - 1, this->getSubject()->getCol()).getYCoord() - yCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord() - yCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() - 1, this->getSubject()->getCol()) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() - 1, this->getSubject()->getCol())->getTag() == "Ghost"){
                this->getSubject()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getRow() - 1, this->getSubject()->getCol())){
                this->setCameraY(yCoord);
                if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() - 1, this->getSubject()->getCol()) != nullptr){
                    this->getSubject()->removePrevious(this->getSubject()->getRow() - 1, this->getSubject()->getCol());
                }
                this->getSubject()->getWorld()->setItem(nullptr, this->getSubject()->getRow(), this->getSubject()->getCol());
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
                this->getSubject()->setHasMoved(false);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow() + 1, this->getSubject()->getCol()).getYCoord() - yCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord() - yCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol()) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol())->getTag() == "Ghost"){
                this->getSubject()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getRow() + 1, this->getSubject()->getCol())){
                this->setCameraY(yCoord);
                if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow() + 1, this->getSubject()->getCol()) != nullptr){
                    this->getSubject()->removePrevious(this->getSubject()->getRow() + 1, this->getSubject()->getCol());
                }

                this->getSubject()->getWorld()->setItem(nullptr, this->getSubject()->getRow(), this->getSubject()->getCol());
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
                this->getSubject()->setHasMoved(false);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol() + 1).getXCoord() - xCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord() - xCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() + 1) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() + 1)->getTag() == "Ghost"){
                this->getSubject()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() + 1)){
                this->setCameraX(xCoord);
                if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() + 1) != nullptr){
                    this->getSubject()->removePrevious(this->getSubject()->getRow(), this->getSubject()->getCol() + 1);
                }
                this->getSubject()->getWorld()->setItem(nullptr, this->getSubject()->getRow(), this->getSubject()->getCol());
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
                this->getSubject()->setHasMoved(false);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol() - 1).getXCoord() - xCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord() - xCoord)){
            // Als het vakje een ghost bevat:
            if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1) != nullptr and this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)->getTag() == "Ghost"){
                this->getSubject()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getSubject()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)){
                this->setCameraX(xCoord);
                if (this->getSubject()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1) != nullptr){
                    this->getSubject()->removePrevious(this->getSubject()->getRow(), this->getSubject()->getCol() - 1);
                }
                this->getSubject()->getWorld()->setItem(nullptr, this->getSubject()->getRow(), this->getSubject()->getCol());
                this->getSubject()->getWorld()->setItem(this->getSubject(), this->getSubject()->getRow(), this->getSubject()->getCol() - 1);
                this->getSubject()->setCol(this->getSubject()->getCol() - 1);
            }
        }else{
            this->setCameraX(xCoord);
        }
    }
    else{
        assert(this->getSubject()->getCurrentDirection() == direction::none);
    }

}

Model::PacMan *GUI::GUIPacMan::getSubject() const {
    return subject;
}

double GUI::GUIPacMan::getXSpeed() const {
    return xSpeed;
}

double GUI::GUIPacMan::getYSpeed() const {
    return ySpeed;
}

GUI::GUIPacMan::~GUIPacMan() = default;
