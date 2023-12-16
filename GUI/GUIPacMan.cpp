//
// Created by Samuel on 16/11/2023.
//

#include "GUIPacMan.h"
using namespace std;


sf::Sprite GUI::GUIPacMan::getSprite() {
    sf::Sprite sprite;
    direction dir = this->getPacManModel()->getCurrentDirection();
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
    else if (dir == direction::down){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 201, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 251, 40, 40));
        }
    }
    else if (dir == direction::left){
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
    if (this->getPacManModel()->isHasMoved()){
        this->updateTextureNr();
    }
    return sprite;
}





int GUI::GUIPacMan::getTextureNr() const {
    return textureNr;
}

void GUI::GUIPacMan::setTextureNr(int nr) {
    GUIPacMan::textureNr = nr;
}

void GUI::GUIPacMan::updateTextureNr() {
    if (this->getTextureNr() < 1){
        this->setTextureNr(this->getTextureNr() + 1);
    }
    else{
        this->setTextureNr(0);
    }
}


void GUI::GUIPacMan::move(const int &ticks) {
    shared_ptr<GUI::Camera> camera = Camera::instance();
    this->getPacManModel()->setHasMoved(true);
    if (this->getPacManModel()->getCurrentDirection() == direction::up){
        double yCoord = this->getCameraY();
        yCoord -= ticks * this->getYSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getPacManModel()->getNextDirection() == direction::right and this->getPacManModel()->canMove(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1)){
            double wallYCoord = camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getYCoord();
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() + this->getXSpeed());
                this->getPacManModel()->setCurrentDirection(direction::right);
                this->getPacManModel()->setNextDirection(direction::none);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

            // Als volgende direction naar links is en hij kan naar links:
        else if (this->getPacManModel()->getNextDirection() == direction::left and this->getPacManModel()->canMove(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() - 1)){
            double wallYCoord = camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getYCoord();
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() - this->getXSpeed());
                this->getPacManModel()->setCurrentDirection(direction::left);
                this->getPacManModel()->setNextDirection(direction::none);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

            // Als de volgende tile een muur is:
        else if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol()) != nullptr and this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol())->getTag() == "Wall"){
            double wallYCoord = camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getYCoord();
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
                this->getPacManModel()->setHasMoved(false);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol()).getYCoord() - yCoord) <
                 abs(camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getYCoord() - yCoord)){
            // Als het vakje een ghost bevat:
            if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol()) != nullptr and this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol())->getTag() == "Ghost"){
                this->getPacManModel()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getPacManModel()->canMove(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol())){
                this->setCameraY(yCoord);
                if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol()) != nullptr){
                    this->getPacManModel()->removePrevious(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol());
                }
                this->getPacManModel()->getWorld()->setItem(nullptr, this->getPacManModel()->getRow(), this->getSubject()->getCol());
                this->getPacManModel()->getWorld()->setItem(this->getSubject(), this->getSubject()->getRow() - 1, this->getSubject()->getCol());
                this->getSubject()->setRow(this->getSubject()->getRow() - 1);
            }
        }else{
            this->setCameraY(yCoord);
        }
    }
    else if (this->getPacManModel()->getCurrentDirection() == direction::down){
        double yCoord = this->getCameraY();
        yCoord += ticks * this->getYSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getPacManModel()->getNextDirection() == direction::right and this->getPacManModel()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() + 1)){
            double wallYCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord();
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() + this->getXSpeed());
                this->getPacManModel()->setCurrentDirection(direction::right);
                this->getPacManModel()->setNextDirection(direction::none);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Als volgende direction naar links is en hij kan naar links:
        else if (this->getPacManModel()->getNextDirection() == direction::left and this->getPacManModel()->canMove(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() - 1)){
            double wallYCoord = camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getYCoord();
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() - this->getXSpeed());
                this->getPacManModel()->setCurrentDirection(direction::left);
                this->getPacManModel()->setNextDirection(direction::none);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol()) != nullptr and this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol())->getTag() == "Wall"){
            double wallYCoord = camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getYCoord();
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
                this->getPacManModel()->setHasMoved(false);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol()).getYCoord() - yCoord) <
                 abs(camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getYCoord() - yCoord)){
            // Als het vakje een ghost bevat:
            if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol()) != nullptr and this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol())->getTag() == "Ghost"){
                this->getPacManModel()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getPacManModel()->canMove(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol())){
                this->setCameraY(yCoord);
                if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol()) != nullptr){
                    this->getPacManModel()->removePrevious(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol());
                }

                this->getPacManModel()->getWorld()->setItem(nullptr, this->getPacManModel()->getRow(), this->getPacManModel()->getCol());
                this->getPacManModel()->getWorld()->setItem(this->getPacManModel(), this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol());
                this->getPacManModel()->setRow(this->getPacManModel()->getRow() + 1);
            }
        }
        else{
            this->setCameraY(yCoord);
        }
    }
    else if (this->getPacManModel()->getCurrentDirection() == direction::right){
        double xCoord = this->getCameraX();
        xCoord += ticks * this->getXSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getPacManModel()->getNextDirection() == direction::up and this->getPacManModel()->canMove(this->getPacManModel()->getRow() - 1, this->getPacManModel()->getCol())){
            double wallXCoord = camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getXCoord();
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() - this->getYSpeed());
                this->getPacManModel()->setCurrentDirection(direction::up);
                this->getPacManModel()->setNextDirection(direction::none);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
        else if (this->getPacManModel()->getNextDirection() == direction::down and this->getPacManModel()->canMove(this->getPacManModel()->getRow() + 1, this->getPacManModel()->getCol())){
            double wallXCoord = camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getXCoord();
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() + this->getYSpeed());
                this->getPacManModel()->setCurrentDirection(direction::down);
                this->getPacManModel()->setNextDirection(direction::none);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1) != nullptr and this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1)->getTag() == "Wall"){
            double wallXCoord = camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getXCoord();
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
                this->getPacManModel()->setHasMoved(false);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1).getXCoord() - xCoord) <
                 abs(camera->getCameraCoords(this->getPacManModel()->getRow(), this->getPacManModel()->getCol()).getXCoord() - xCoord)){
            // Als het vakje een ghost bevat:
            if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1) != nullptr and this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1)->getTag() == "Ghost"){
                this->getPacManModel()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getPacManModel()->canMove(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1)){
                this->setCameraX(xCoord);
                if (this->getPacManModel()->getWorld()->getItem(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1) != nullptr){
                    this->getPacManModel()->removePrevious(this->getPacManModel()->getRow(), this->getPacManModel()->getCol() + 1);
                }
                this->getPacManModel()->getWorld()->setItem(nullptr, this->getPacManModel()->getRow(), this->getPacManModel()->getCol());
                this->getPacManModel()->getWorld()->setItem(this->getSubject(), this->getSubject()->getRow(), this->getSubject()->getCol() + 1);
                this->getSubject()->setCol(this->getSubject()->getCol() + 1);
            }
        }else{
            this->setCameraX(xCoord);
        }
    }
    else if (this->getPacManModel()->getCurrentDirection() == direction::left){
        double xCoord = this->getCameraX();
        xCoord -= ticks * this->getXSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getPacManModel()->getNextDirection() == direction::up and this->getPacManModel()->canMove(this->getSubject()->getRow() - 1, this->getSubject()->getCol())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() - this->getYSpeed());
                this->getPacManModel()->setCurrentDirection(direction::up);
                this->getPacManModel()->setNextDirection(direction::none);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
        else if (this->getPacManModel()->getNextDirection() == direction::down and this->getPacManModel()->canMove(this->getSubject()->getRow() + 1, this->getSubject()->getCol())){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() + this->getYSpeed());
                this->getPacManModel()->setCurrentDirection(direction::down);
                this->getPacManModel()->setNextDirection(direction::none);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getPacManModel()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1) != nullptr and this->getPacManModel()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)->getTag() == "Wall"){
            double wallXCoord = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
                this->getPacManModel()->setHasMoved(false);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol() - 1).getXCoord() - xCoord) <
                 abs(camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord() - xCoord)){
            // Als het vakje een ghost bevat:
            if (this->getPacManModel()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1) != nullptr and this->getPacManModel()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)->getTag() == "Ghost"){
                this->getPacManModel()->getWorld()->die();
            }
                // Als het volgende vakje geen muur is: gaan
            else if (this->getPacManModel()->canMove(this->getSubject()->getRow(), this->getSubject()->getCol() - 1)){
                this->setCameraX(xCoord);
                if (this->getPacManModel()->getWorld()->getItem(this->getSubject()->getRow(), this->getSubject()->getCol() - 1) != nullptr){
                    this->getPacManModel()->removePrevious(this->getSubject()->getRow(), this->getSubject()->getCol() - 1);
                }
                this->getPacManModel()->getWorld()->setItem(nullptr, this->getSubject()->getRow(), this->getSubject()->getCol());
                this->getPacManModel()->getWorld()->setItem(this->getSubject(), this->getSubject()->getRow(), this->getSubject()->getCol() - 1);
                this->getSubject()->setCol(this->getSubject()->getCol() - 1);
            }
        }else{
            this->setCameraX(xCoord);
        }
    }
    else{
        assert(this->getPacManModel()->getCurrentDirection() == direction::none);
    }

}

double GUI::GUIPacMan::getXSpeed() const {
    return xSpeed;
}

double GUI::GUIPacMan::getYSpeed() const {
    return ySpeed;
}

std::shared_ptr<Model::PacMan> GUI::GUIPacMan::getPacManModel() const {
    return pacManModel.lock();
}

GUI::GUIPacMan::GUIPacMan(const shared_ptr<Model::PacMan>& subject) : EntityView(subject) {
    textureNr = 0;
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    pacManModel = subject;
    shared_ptr<Camera> cam = Camera::instance();
    xSpeed = cam->getXSpeed();
    ySpeed = cam->getYSpeed();
}

GUI::GUIPacMan::~GUIPacMan() = default;
