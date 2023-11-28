//
// Created by Samuel on 19/11/2023.
//

#ifndef PAC_MAN_PACMAN_H
#define PAC_MAN_PACMAN_H
#include "EntityModel.h"
#include "Subject.h"
#include "Observer.h"

class Model::PacMan: public Model::EntityModel{
    Model::World* world;
    direction currentDirection;
    direction nextDirection;
    double xSpeed;
    double ySpeed;
    bool hasMoved;
    int score;
    int startRow;
    int startCol;
public:
    /*
     * De constructor van de PacMan class
     */
    PacMan(int row, int col, World *world);
    /*
     * Beweegt Pac-Man
     */
    void move(const int &ticks);

    /*
     * Sterven van pacman
     */
    void die();

    void removePrevious(const int &row, const int &col);

    /*
    * Verandert de richting afhankelijk van de volgende richting
    */
    void moveDirection(const direction &dir);

    [[nodiscard]] bool canMove(const int &row, const int &col) const;

    [[nodiscard]] const direction &getCurrentDirection() const;

    void setCurrentDirection(const direction &dir);

    [[nodiscard]] Model::World *getWorld() const;

    void setWorld(World *pWorld);

    [[nodiscard]] double getXSpeed() const;

    void setXSpeed(double speed);

    [[nodiscard]] double getYSpeed() const;

    void setYSpeed(double speed);

    [[nodiscard]] const direction &getNextDirection() const;

    void setNextDirection(const direction &dir);

    [[nodiscard]] bool isHasMoved() const;

    void setHasMoved(bool moved);

    [[nodiscard]] int getScore() const;

    void setScore(int newScore);

    [[nodiscard]] int getStartRow() const;

    void setStartRow(int row);

    [[nodiscard]] int getStartCol() const;

    void setStartCol(int col);
};


#endif //PAC_MAN_PACMAN_H
