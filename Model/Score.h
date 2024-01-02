//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_SCORE_H
#define PAC_MAN_SCORE_H
#include "Observer.h"
#include "Collectable.h"
#include "ctime"
#include "Stopwatch.h"

class Model::Score: public Model::Observer {
    int score;
    std::string scoreBoardFileName;
    double lastCollected;
    double levelStartTime;
    double benchMarkTime;
    std::weak_ptr<Model::World> world;
    std::vector<int> scoreBoard;
    int livesLeft;
    int coinsCollected;
public:
    explicit Score(const std::weak_ptr<Model::World> &world);

    /*
     * Laadt het scoreboard in van de .txt file
     */
    void loadScoreBoard();

    /*
     * Voegt laatste score toe aan scoreboard als deze in de top 5 zit en stopt deze in de .txt file
     */
    void storeScoreBoard();

    void nextLevel();

    void restart();

    void collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) override;

    void ghostConsumed();

    void update(const double &seconds) override;

    double getAmplifyingFactor();

    [[nodiscard]] int getScore() const;

    [[nodiscard]] const std::string &getScoreBoardFileName() const;

    [[nodiscard]] double getLastCollected() const;

    [[nodiscard]] double getLevelStartTime() const;

    [[nodiscard]] const std::weak_ptr<Model::World> &getWorld() const;

    void setLastCollected(double collected);

    void setLevelStartTime(double startTime);

    [[nodiscard]] double getBenchMarkTime() const;

    void setBenchMarkTime(double d);

    void setScore(int i);

    [[nodiscard]] const std::vector<int> &getScoreBoard() const;

    [[nodiscard]] int getLivesLeft() const;

    void setLivesLeft(int i);

    [[nodiscard]] int getCoinsCollected() const;

    void setCoinsCollected(int i);
};


#endif //PAC_MAN_SCORE_H
