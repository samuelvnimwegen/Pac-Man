//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STATE_H
#define PAC_MAN_STATE_H
#include "../Model/Subject.h"
#include "../Model/Stopwatch.h"

namespace GUI{
    class ConcreteFactory;
    class EntityView;
    class Camera;
    class Game;
    class Coin;
    class Ghost;
    class PacMan;
    class Wall;
    class LevelState;
    class MenuState;
    class PausedState;
    class State;
    class StateManager;
    class VictoryState;
    class Fruit;
    class Window;
    class GameOverState;
    class EscapeWall;
}
enum key{space, backspace, escape, noKey, leftMouseButton, startButton};
enum stateTag{victory, menu, paused, level, gameOver};

class GUI::State {
    stateTag tag;
    std::weak_ptr<StateManager> stateManager;
    std::weak_ptr<Model::World> world;
public:
    State(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world);

    virtual ~State();

    virtual void update(const key &key) = 0;

    [[nodiscard]] stateTag getTag() const;

    void setTag(const stateTag &stateTag);

    [[nodiscard]] const std::weak_ptr<StateManager> &getStateManager() const;

    [[nodiscard]] const std::weak_ptr<Model::World> &getWorld() const;
};


#endif //PAC_MAN_STATE_H
