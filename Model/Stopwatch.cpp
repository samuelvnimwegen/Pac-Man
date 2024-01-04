//
// Created by Samuel on 16/11/2023.
//

#include "Stopwatch.h"

std::shared_ptr<Model::Stopwatch> Model::Stopwatch::m_pStopwatch = nullptr;

Model::Stopwatch::Stopwatch(){
    levelStartTime = 0;
    pausedLevelTime = 0;
    totalPauseTime = 0;
    totalTime = clock();
}

double Model::Stopwatch::getDeltaTime() {
    auto elapsedTime = double(clock() - totalTime) / double(CLOCKS_PER_SEC);
    while (elapsedTime <= 0.0){
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

double Model::Stopwatch::getLevelTime() const {
    return double(clock() - levelStartTime - totalPauseTime) / double(CLOCKS_PER_SEC);
}

void Model::Stopwatch::startLevel() {
    levelStartTime = clock();
    totalPauseTime = 0;
}

void Model::Stopwatch::pause() {
    pausedLevelTime = clock();
}

void Model::Stopwatch::unpause() {
    totalPauseTime += clock() - pausedLevelTime;
}
