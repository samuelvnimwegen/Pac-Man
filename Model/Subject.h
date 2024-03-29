//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_SUBJECT_H
#define PAC_MAN_SUBJECT_H
#include "iostream"
#include "vector"
#include "memory"

namespace Model{
    class Subject;
    class EntityModel;
    class Coin;
    class Collectable;
    class Fruit;
    class Ghost;
    class EscapeWall;
    class Wall;
    class PacMan;
    class World;
    class Observer;
    class Score;
    class Random;
    class Stopwatch;
    class AbstractFactory;
    class GhostStateManager;
    class GhostIdleState;
    class GhostState;
    class GhostChasingState;
    class GhostFrightenedState;
    class GhostResetState;
    class GhostEatenState;
    class GhostIdleFrightenedState;
    class DijkstraGraph;
    class DijkstraTransition;
    class DijkstraPoint;

}
enum direction {right, down, left, up, none};

enum color{red, pink, blue, orange, green, purple};

enum entityTag{pacMan, ghost, coin, fruit, wall, noneTag, escapeWall};

class Model::Subject {
    std::vector<std::shared_ptr<Model::Observer>> observers;
public:
    Subject();

    [[nodiscard]] const std::vector<std::shared_ptr<Model::Observer>> &getObservers() const;

    void addObserver(const std::shared_ptr<Model::Observer>& observer);
};


#endif //PAC_MAN_SUBJECT_H
