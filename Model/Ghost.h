//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H
#include "EntityModel.h"
#include "Subject.h"
#include "GhostStateManager.h"
#include "GhostIdleState.h"

class Model::Ghost: public Model::EntityModel{
    std::weak_ptr<Model::World> world;
    direction startDirection;
    direction currentDirection;
    direction nextDirection;
    std::shared_ptr<Model::GhostStateManager> stateManager;
    int startRow;
    int startCol;
    double waitTime; // Time before the ghost is released from the spawnRegion
    double speed;
    double defaultSpeed;
    bool frightened; // Toggle bool that turns 'true' when a fruit gets eaten, and is made 'false' next update
    double frightenTime; // Last timestamp where the ghost was frightened
public:
    Ghost(int row, int col, const std::shared_ptr<Model::World>& world);

    /*
     * Beweegt de ghost
     */
    void move(const double &nanoSeconds);

    /*
     * Update de ghost na elk update-interval
     */
    void update(const double &nanoSeconds) override;

    /*
     * Verandert de richting van de ghost
     */
    void changeDirection();

    /*
     * Ghost gaat weer terug naar spawn
     */
    void reset();

    /*
     * Zoekt de beste dijkstra richting met het Dijkstra-algoritme (naar de Pac-Man)
     */
    direction getDijkstraDirection();

    /*
     * Zoekt de Dijkstra-richting naar de spawn
     */
    direction getDijkstraDirectionSpawn();
    /*
     * Functie die bij de initial fear zorgt dat alle ghosts wegrennen van pacman:
     */
    void initialFearMove();

    [[nodiscard]] bool canMove(const int &row, const int &col) ;

    bool canMove(const direction &direction);

    [[nodiscard]] int getManhattanDistancePacMan(const direction &direction);

    int getManhattanDistanceSpawn(const direction &direction);

    [[nodiscard]] int getStartRow() const;

    [[nodiscard]] int getStartCol() const;

    [[nodiscard]] direction getCurrentDirection() const;

    void setCurrentDirection(direction direction);

    [[nodiscard]] direction getNextDirection() const;

    void setNextDirection(direction direction);

    [[nodiscard]]  std::shared_ptr<Model::World> getWorld() ;

    [[nodiscard]] double getSpeed() const;

    [[nodiscard]] direction getStartDirection() const;

    void setStartDirection(direction direction);

    [[nodiscard]] const std::shared_ptr<Model::GhostStateManager> &getStateManager() const;

    [[nodiscard]] double getWaitTime() const;

    void setWaitTime(double seconds);

    [[nodiscard]] bool isFrightened() const;

    void setFrightened(bool b);

    void setSpeed(double d);

    [[nodiscard]] double getDefaultSpeed();

    [[nodiscard]] double getFrightenTime() const;

    void setFrightenTime(double d);
};
template<typename T> T templateMax(const T &x, const T &y);


#endif //PAC_MAN_GHOST_H
