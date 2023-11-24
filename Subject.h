//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_SUBJECT_H
#define PAC_MAN_SUBJECT_H
#include "iostream"
#include "vector"
namespace Model{
    class Subject;
    class EntityModel;
    class Coin;
    class Collectable;
    class Fruit;
    class Ghost;
    class Wall;
    class PacMan;
    class World;
    class Observer;
    class Score;
    class Random;
    class Stopwatch;
    class AbstractFactory;
}
namespace GUI{
    class ConcreteFactory;
    class EntityView;
    class Fruit;
    class Camera;
    class Game;
    class GUICoin;
    class GUIGhost;
    class GUIPacMan;
    class GUIWall;
    class LevelState;
    class MenuState;
    class PausedState;
    class State;
    class StateManager;
    class VictoryState;
}
enum direction {up, down, left, right};

class Model::Subject {
    int row;
    int col;
public:
    Subject(int row, int col);

    [[nodiscard]] int getRow() const;

    void setRow(int row);

    [[nodiscard]] virtual bool isConsumed() const = 0;

    [[nodiscard]] int getCol() const;

    void setCol(int c);
};


#endif //PAC_MAN_SUBJECT_H
