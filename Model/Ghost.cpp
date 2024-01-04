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

    // Slechts mogelijke richting moet ook bepaald worden voor in feared mode
    int maxDistance = 0;
    direction worstDirection = direction::none;

    // Voor alle mogelijke directions afgaan of ze viable zijn en of ze de beste of slechtste direction zijn:
    for (auto direction: {direction::up, direction::down, direction::left, direction::right}){
        if (this->canMove(direction)){
            viableDirections.push_back(direction);

            // Afstand tot pacman of tot de spawn in het geval van een reset (dus als de ghost is opgegeten)
            int distance = this->getManhattanDistancePacMan(direction);
            if (this->getStateManager()->getCurrentTag() == ghostStateTag::reset){
                distance = this->getManhattanDistanceSpawn(direction);
            }
            if (distance < minDistance){
                minDistance = distance;
                bestDirection = direction;
            }
            if (distance > maxDistance){
                maxDistance = distance;
                worstDirection = direction;
            }
        }
    }
    // Als de ghost chasing is en niet op dezelfde tile staat als pacman, dijkstra-direction krijgen:
    if (this->getStateManager()->getCurrentTag() == chasing){
        auto pacMan = this->getWorld()->getPacMan();
        if (toTile(this->getX()) != toTile(pacMan->getX()) or toTile(this->getY()) != toTile(pacMan->getY())){
            auto dijkstraDirection = this->getDijkstraDirection();
            if (canMove(dijkstraDirection)){
                bestDirection = dijkstraDirection;
            }
        }
    }

    // Als de ghost chasing is en niet op dezelfde tile staat als pacman, dijkstra-direction krijgen:
    if (this->getStateManager()->getCurrentTag() == ghostStateTag::reset){
        auto pacMan = this->getWorld()->getPacMan();
        if (toTile(this->getX()) != this->getStartCol() or toTile(this->getY()) != this->getStartRow()){
            auto dijkstraDirection = this->getDijkstraDirectionSpawn();
            if (canMove(dijkstraDirection)){
                bestDirection = dijkstraDirection;
            }
        }
    }

    // Dit is voor hoeken en intersecties:
    if (!canMove(this->getCurrentDirection()) or viableDirections.size() >= 3){
        // Checken of de ghost in de spawn-region is en aan het chasen is:
        auto col = toTile(this->getX());
        auto row = toTile(this->getY());
        auto posPair = make_pair(row, col);
        auto spawnPairs = this->getWorld()->getSpawnRegion();
        bool inSpawn = std::count(spawnPairs.begin(), spawnPairs.end(), posPair);
        bool chasingOrFrightened = this->getStateManager()->getCurrentTag() == chasing or this->getStateManager()->getCurrentTag() == ghostStateTag::frightened;
        // Random getal tussen 0 en 1 berekenen, als deze kleiner is dan 0.5 beste richting kiezen of als de ghost in
        // de spawn-region is:
        double randomDouble = randomGenerator->getRandomDouble(0, 1);
        if (templateMax(randomDouble, 0.5) == 0.5 or (inSpawn and chasingOrFrightened)){
            auto direction = bestDirection;
            // Als de ghost frightened is moet hij de slechtste richting nemen:
            if (this->getStateManager()->getCurrentTag() == ghostStateTag::frightened){
                direction = worstDirection;
            }

            // Als de current en de nieuwe direction allebei up-down of niet up-down zijn: meteen van richting veranderen
            if (std::count(upDown.begin(), upDown.end(), this->getCurrentDirection()) ==
                std::count(upDown.begin(), upDown.end(), direction)){
                this->setCurrentDirection(direction);
                this->setNextDirection(direction::none);
            }
            // Als de nieuwe direction left-right is en de oude up-down of omgekeerd: draaien bij volgende mogelijkheid
            else{
                this->setNextDirection(direction);
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


int Model::Ghost::getStartRow() const {
    return startRow;
}

int Model::Ghost::getStartCol() const {
    return startCol;
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
    this->setCurrentDirection(this->getStartDirection());
    this->setNextDirection(none);
    this->setX(getStartCol());
    this->setY(getStartRow());
    this->setFrightenTime(0);
    this->getStateManager()->reset();
}

void Model::Ghost::setSpeed(double d) {
    Ghost::speed = d;
}

template<typename T>
T templateMax(const T &x, const T &y) {
    return (x > y)?  x: y;
}