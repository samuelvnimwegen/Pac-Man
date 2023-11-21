//
// Created by Samuel on 16/11/2023.
//

#include "Stopwatch.h"

Stopwatch::Stopwatch(){
    tickTime = sf::milliseconds(1);
}

int Stopwatch::getTicks() {
    auto elapsedTime = clock.getElapsedTime();
    int steps = int(elapsedTime / tickTime);
    if (steps == 0){
        return 1;
    }
    clock.restart();
    return steps;
}
