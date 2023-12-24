//
// Created by Samuel on 16/11/2023.
//

#include "Ghost.h"
#include "limits"
#include "Random.h"
#include "algorithm"
using namespace std;

void Model::Ghost::changeDirection() {
    // Random number generator voor later
    auto randomGenerator = Model::Random::instance();

    // Vector voor up/down en left/right voor later:
    vector<direction> upDown = {direction::up, direction::down};
    vector<direction> leftRight = {direction::left, direction::right};

    // Maximale integer waarde zodat de eerste mogelijke manhattan-afstand altijd kleiner is
    int minDistance = std::numeric_limits<int>::max();
    direction bestDirection = direction::none;
    vector<direction> viableDirections;

    // Voor alle mogelijke directions afgaan of ze viable zijn en of ze de beste direction zijn:
    for (auto direction: {direction::up, direction::down, direction::left, direction::right}){
        if (this->canMove(direction)){
            viableDirections.push_back(direction);
            int distance = this->getManhattanDistance(direction);
            if (distance < minDistance){
                minDistance = distance;
                bestDirection = direction;
            }
        }
    }

    // Dit is voor hoeken en intersecties:
    if (!canMove(this->getCurrentDirection()) or viableDirections.size() >= 3){
        // Random getal tussen 0 en 1 berekenen, als deze kleiner is dan 0.5 beste richting kiezen:
        double randomDouble = randomGenerator->getRandomDouble(0, 1);
        if (templateMax(randomDouble, 0.5) == 0.5){
            // Als de current en de nieuwe direction allebei up-down of niet up-down zijn: meteen van richting veranderen
            if (std::count(upDown.begin(), upDown.end(), this->getCurrentDirection()) ==
                std::count(upDown.begin(), upDown.end(), bestDirection)){
                this->setCurrentDirection(bestDirection);
                this->setNextDirection(direction::none);
            }
            // Als de nieuwe direction left-right is en de oude up-down of omgekeerd: draaien bij volgende mogelijkheid
            else{
                this->setNextDirection(bestDirection);
            }
        }
        // Anders random viable richting:
        else{
            int i = randomGenerator->getRandomInt(0, int(viableDirections.size()) - 1);
            direction randomDirection = viableDirections.at(i);
            // Als de current en de nieuwe direction allebei up-down of niet up-down zijn: meteen van richting veranderen
            if (std::count(upDown.begin(), upDown.end(), this->getCurrentDirection()) ==
                    std::count(upDown.begin(), upDown.end(), randomDirection)){
                this->setCurrentDirection(randomDirection);
                this->setNextDirection(direction::none);
            }
            // Als de nieuwe direction left-right is en de oude up-down of omgekeerd: draaien bij volgende mogelijkheid
            else{
                this->setNextDirection(randomDirection);
            }
        }
    }

}

bool Model::Ghost::isJustTurned() const {
    return justTurned;
}

void Model::Ghost::setJustTurned(bool turned) {
    Ghost::justTurned = turned;
}

const string &Model::Ghost::getCurrentState() const {
    return currentState;
}

void Model::Ghost::setCurrentState(const string &state) {
    Ghost::currentState = state;
}

int Model::Ghost::getStartRow() const {
    return startRow;
}

void Model::Ghost::setStartRow(int row) {
    Ghost::startRow = row;
}

int Model::Ghost::getStartCol() const {
    return startCol;
}

void Model::Ghost::setStartCol(int col) {
    Ghost::startCol = col;
}


color Model::Ghost::getColor() const {
    return ghostColor;
}

void Model::Ghost::setColor(color col) {
    Ghost::ghostColor = col;
}

direction Model::Ghost::getCurrentDirection() const {
    return currentDirection;
}

void Model::Ghost::setCurrentDirection(direction direction) {
    Ghost::currentDirection = direction;
}

direction Model::Ghost::getNextDirection() const {
    return nextDirection;
}

void Model::Ghost::setNextDirection(direction direction) {
    Ghost::nextDirection = direction;
}


void Model::Ghost::reset() {
    this->setCurrentDirection(up);
    this->setNextDirection(none);
    this->setX(getStartCol());
    this->setY(getStartRow());
}

template<typename T>
T templateMax(const T &x, const T &y) {
    return (x > y)?  x: y;
}