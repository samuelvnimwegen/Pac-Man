//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STOPWATCH_H
#define PAC_MAN_STOPWATCH_H
#include "chrono"
#include "Subject.h"

class Model::Stopwatch {
private:
    clock_t totalTime;
    static std::shared_ptr<Model::Stopwatch> m_pStopwatch;
    clock_t pausedLevelTime;
    clock_t totalPauseTime;
    clock_t levelStartTime;

protected:
    explicit Stopwatch();
public:
    static std::shared_ptr<Model::Stopwatch> instance();

    Stopwatch(Model::Stopwatch &other) = delete;

    void operator=(const Model::Stopwatch&) = delete;

    double getDeltaTime();

    [[nodiscard]] static double getTotalSeconds() ;

    [[nodiscard]] double getLevelTime() const;

    void startLevel();

    void pause();

    void unpause();
};


#endif //PAC_MAN_STOPWATCH_H
