//
// Created by Samuel on 02/01/2024.
//

#include "DijkstraGraph.h"
#include "DijkstraPoint.h"
#include "DijkstraTransition.h"
#include "Random.h"

#include <cassert>

Model::DijkstraPoint::DijkstraPoint(int x, int y) : x(x), y(y) {
    explored = false;
}

void Model::DijkstraPoint::addTransition(std::unique_ptr<DijkstraTransition> transition) {
    transitions.push_back(std::move(transition));
}

int Model::DijkstraPoint::getX() const {
    return x;
}

int Model::DijkstraPoint::getY() const {
    return y;
}

bool Model::DijkstraPoint::isExplored() const {
    return explored;
}

void Model::DijkstraPoint::setExplored(bool b) {
    DijkstraPoint::explored = b;
}

bool Model::DijkstraPoint::canGoTo(const std::weak_ptr<DijkstraPoint>& dijkstraPoint) {
    for (int i = 0; i < this->transitions.size(); ++i){
        if (transitions.at(i)->getNextPoint().lock() and dijkstraPoint.lock()){
            if (transitions.at(i)->getNextPoint().lock()->getX() == dijkstraPoint.lock()->getX() and
            transitions.at(i)->getNextPoint().lock()->getY() == dijkstraPoint.lock()->getY()){
                return true;
            }
        }
    }
    return false;
}

Model::DijkstraTransition::DijkstraTransition(const std::weak_ptr<DijkstraPoint> &nextPoint): nextPoint(nextPoint) {}

const std::weak_ptr<Model::DijkstraPoint> &Model::DijkstraTransition::getNextPoint() const {
    return nextPoint;
}


Model::DijkstraGraph::DijkstraGraph(const std::vector<std::vector<std::shared_ptr<Model::Wall>>> &world,
                             const std::shared_ptr<DijkstraPoint> &beginPoint,
                             const std::shared_ptr<DijkstraPoint> &endPoint) : world(world), beginPoint(beginPoint),
                                                                               endPoint(endPoint) {
    points.push_back(beginPoint);
    points.push_back(endPoint);
    this->buildDijkstraMap();
}

void Model::DijkstraGraph::buildDijkstraMap() {
    // Eerst lege map bouwen:
    for (int i = 0; i < this->getWorld().size(); ++i){
        std::vector<std::shared_ptr<DijkstraPoint>> row;
        row.reserve(this->getWorld().size());
        for (int j = 0; j < this->getWorld().at(0).size(); ++j){
            row.push_back(nullptr);
        }
        dijkstraMap.push_back(row);
    }
    // Aantal checks of dat het begin en eindvlakje geen muren zijn
    auto beginX = this->getBeginPoint()->getX();
    auto beginY = this->getBeginPoint()->getY();
    auto startWorldItem = this->getWorld().at(beginY).at(beginX);
    assert(startWorldItem == nullptr);
    auto endX = this->getEndPoint()->getX();
    auto endY = this->getEndPoint()->getY();
    auto endWorldItem = this->getWorld().at(endY).at(endX);
    assert(endWorldItem == nullptr);

    dijkstraMap.at(beginY).at(beginX) = this->getBeginPoint();
    std::vector<std::shared_ptr<DijkstraPoint>> nextPoints = {this->getBeginPoint()};
    bool done = false;
    while (!done){
        std::vector<std::shared_ptr<DijkstraPoint>> queue;
        for (const auto& point: nextPoints){
            point->setExplored(true);
            auto x = point->getX();
            auto y = point->getY();
            // Als het eindpunt bereikt is, stoppen met de while loop
            if (x == endX and y == endY){
                done = true;
            }
            // Alle buur-vakjes kijken of er al iets is ingevuld, anders naartoe gaan en in queue zetten
            std::vector<std::pair<int, int>> neighbours = {{y + 1, x}, {y - 1, x}, {y, x + 1}, {y, x - 1}};
            randomSort(neighbours); // Random sorteren zodat ze bij 2 even snelle paden niet altijd dezelfde pakken
            for (auto pair: neighbours){
                if (this->getWorld().at(pair.first).at(pair.second) == nullptr and
                dijkstraMap.at(pair.first).at(pair.second) == nullptr){
                    auto newPoint = std::make_shared<DijkstraPoint>(pair.second, pair.first);
                    dijkstraMap.at(pair.first).at(pair.second) = newPoint;
                    point->addTransition(std::make_unique<DijkstraTransition>(newPoint));
                    queue.push_back(newPoint);
                }
            }
        }
        nextPoints = queue;
    }
}

const std::shared_ptr<Model::DijkstraPoint> &Model::DijkstraGraph::getBeginPoint() const {
    return beginPoint;
}

const std::shared_ptr<Model::DijkstraPoint> &Model::DijkstraGraph::getEndPoint() const {
    return endPoint;
}

const std::vector<std::vector<std::shared_ptr<Model::Wall>>> &Model::DijkstraGraph::getWorld() const {
    return world;
}

void Model::DijkstraGraph::printDijkstraMap() {
    for (int i = 0; i < dijkstraMap.size(); ++i){
        for (int j = 0; j < dijkstraMap.at(0).size(); ++j){
            if (dijkstraMap.at(i).at(j) != nullptr){
                std::cout << "X\t";
            }
            else if (this->getWorld().at(i).at(j) != nullptr){
                std::cout << "-\t";
            }
            else {
                std::cout << " \t";
            }
        }
        std::cout << std::endl;
    }
}

std::vector<direction> Model::DijkstraGraph::getDijkstraPath() {
    auto currentPoint = this->getEndPoint();
    bool done = false;
    std::vector<direction> path;
    while (!done){
        auto x = currentPoint->getX();
        auto y = currentPoint->getY();
        // Richtingen in tegengestelde volgorde van hoe ze in de enum 'direction' staan, bv. {boven, rechts} -> {onder, links}
        std::vector<std::pair<int, int>> neighbours = {{y, x - 1}, {y - 1, x}, {y, x + 1}, {y + 1, x}};

        // We zoeken telkens een aanliggend vakje wat naar het huidige vakje wijst, we werken dus in principe van het einde
        // naar het startpunt.
        bool neighbourFound = false;
        int i = 0;
        while (!neighbourFound){
            assert(i < neighbours.size()); // Geen neighbour gevonden die naar het vakje wijst
            auto pair = neighbours.at(i);
            auto neighbour = dijkstraMap.at(pair.first).at(pair.second);
            if (neighbour != nullptr and neighbour->isExplored()){
                // Checken of neighbour naar currentPoint kan:
                if (neighbour->canGoTo(currentPoint)){
                    neighbourFound = true;
                    currentPoint = neighbour;
                    // Als dit punt het startpunt is, zijn we klaar
                    if (neighbour->getX() == this->getBeginPoint()->getX() and neighbour->getY() == this->getBeginPoint()->getY()){
                        done = true;
                    }
                    path.insert(path.begin(), direction(i));
                }
            }
            ++i;
        }
    }
    return path;
}




