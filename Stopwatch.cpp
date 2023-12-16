//
// Created by Samuel on 16/11/2023.
//

#include "Stopwatch.h"
std::shared_ptr<Model::Stopwatch> Model::Stopwatch::m_pStopwatch = nullptr;

Model::Stopwatch::Stopwatch(){
    tickTime = sf::milliseconds(1);
}

int Model::Stopwatch::getTicks() {
    auto elapsedTime = clock.getElapsedTime();
    int steps = int(elapsedTime / tickTime);
    if (steps == 0){
        return 1;
    }
    clock.restart();
    return steps;
}

std::shared_ptr<Model::Stopwatch> Model::Stopwatch::instance() {
    if (m_pStopwatch == nullptr){
        m_pStopwatch = std::shared_ptr<Model::Stopwatch>(new Stopwatch);
    }
    return m_pStopwatch;
}
