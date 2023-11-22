//
// Created by Samuel on 19/11/2023.
//

#ifndef PAC_MAN_PACMAN_H
#include "EntityModel.h"
#define PAC_MAN_PACMAN_H


class World;
class PacMan: public EntityModel{
    World* world;
    string currentDirection;
    string nextDirection;
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
    void moveDirection(const string &direction);

    [[nodiscard]] bool canMove(const int &row, const int &col) const;

    [[nodiscard]] const string &getCurrentDirection() const;

    void setCurrentDirection(const string &direction);

    [[nodiscard]] World *getWorld() const;

    void setWorld(World *pWorld);

    [[nodiscard]] double getXSpeed() const;

    void setXSpeed(double speed);

    [[nodiscard]] double getYSpeed() const;

    void setYSpeed(double speed);

    [[nodiscard]] const string &getNextDirection() const;

    void setNextDirection(const string &direction);

    [[nodiscard]] bool isHasMoved() const;

    void setHasMoved(bool moved);

    [[nodiscard]] int getScore() const;

    void setScore(int newScore);

    int getStartRow() const;

    void setStartRow(int row);

    int getStartCol() const;

    void setStartCol(int col);
};


#endif //PAC_MAN_PACMAN_H
