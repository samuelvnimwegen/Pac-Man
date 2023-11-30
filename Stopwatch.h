//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STOPWATCH_H
#define PAC_MAN_STOPWATCH_H
#include "SFML/Graphics.hpp"
#include "Subject.h"

class Model::Stopwatch {
private:
    sf::Time tickTime;
    sf::Clock clock;
    static Stopwatch* m_pStopwatch;
protected:
    explicit Stopwatch();
public:
    static Stopwatch* instance();

    Stopwatch(Model::Stopwatch &other) = delete;

    void operator=(const Model::Stopwatch&) = delete;


    int getTicks();
};


#endif //PAC_MAN_STOPWATCH_H
