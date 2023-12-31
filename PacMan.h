//
// Created by Samuel on 19/11/2023.
//

#ifndef PAC_MAN_PACMAN_H
#define PAC_MAN_PACMAN_H
#include "EntityModel.h"
#include "Subject.h"
#include "Observer.h"
#include "Stopwatch.h"

class Model::PacMan: public Model::EntityModel{
    std::weak_ptr<Model::World> world;
    direction currentDirection;
    direction nextDirection;
    double speed;
    bool hasMoved;
    bool dead;
    double deathTime;
    int startRow;
    int startCol;
public:
    /*
     * De constructor van de PacMan class
     */
    PacMan(int row, int col, const std::shared_ptr<World>& world);
    /*
     * Beweegt Pac-Man
     */
    void move(const double &seconds);

    void update(const double &seconds) override;

    /*
     * Resetten van pacman
     */
    void reset();

    /*
    * Verandert de richting afhankelijk van de volgende richting
    */
    void changeDirection(const direction &dir);

    void die();

    [[nodiscard]] bool canMove(const int &row, const int &col);

    [[nodiscard]] const direction &getCurrentDirection() const;

    void setCurrentDirection(const direction &dir);

    std::shared_ptr<Model::World> getWorld() ;

    [[nodiscard]] const direction &getNextDirection() const;

    void setNextDirection(const direction &dir);

    [[nodiscard]] bool isHasMoved() const;

    void setHasMoved(bool moved);

    [[nodiscard]] int getStartRow() const;

    [[nodiscard]] int getStartCol() const;

    [[nodiscard]] double getSpeed() const;

    [[nodiscard]] bool isDead() const;

    void setDead(bool b);

    [[nodiscard]] double getDeathTime() const;

    void setDeathTime(double time);


};



#endif //PAC_MAN_PACMAN_H
