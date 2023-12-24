//
// Created by Samuel on 16/11/2023.
//

#include "Stopwatch.h"
typedef std::chrono::high_resolution_clock Clock;

std::shared_ptr<Model::Stopwatch> Model::Stopwatch::m_pStopwatch = nullptr;

Model::Stopwatch::Stopwatch(){
    totalTime = clock();
};

double Model::Stopwatch::getDeltaTime() {
    auto elapsedTime = double(clock() - totalTime) / double(CLOCKS_PER_SEC);
    while (elapsedTime == 0.0){
        elapsedTime = double(clock() - totalTime) / (double) CLOCKS_PER_SEC;
    }

    totalTime = clock();
    return elapsedTime;
}

std::shared_ptr<Model::Stopwatch> Model::Stopwatch::instance() {
    if (m_pStopwatch == nullptr){
        m_pStopwatch = std::shared_ptr<Model::Stopwatch>(new Stopwatch);
    }
    return m_pStopwatch;
}

double Model::Stopwatch::getTotalSeconds() {
    auto elapsedTime = double(clock()) / double(CLOCKS_PER_SEC);
    return elapsedTime;
}
