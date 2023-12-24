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
protected:
    explicit Stopwatch();
public:
    static std::shared_ptr<Model::Stopwatch> instance();

    Stopwatch(Model::Stopwatch &other) = delete;

    void operator=(const Model::Stopwatch&) = delete;

    double getDeltaTime();

    [[nodiscard]] static double getTotalSeconds() ;
};


#endif //PAC_MAN_STOPWATCH_H
