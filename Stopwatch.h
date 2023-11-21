//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STOPWATCH_H
#define PAC_MAN_STOPWATCH_H
#include "SFML/Graphics.hpp"

class Stopwatch {
    sf::Time tickTime;
    sf::Clock clock;
public:
    explicit Stopwatch();

    int getTicks();
};


#endif //PAC_MAN_STOPWATCH_H
