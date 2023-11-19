//
// Created by Samuel on 16/11/2023.
//

#include "Stopwatch.h"

Stopwatch::Stopwatch(){
    tickTime = sf::milliseconds(12);
}

int Stopwatch::getSteps() {
    auto elapsedTime = clock.getElapsedTime();
    int steps = int(elapsedTime / tickTime);
    clock.restart();
    return steps;
}
