//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H
#include "Subject.h"
#include "SFML/Graphics.hpp"

class Model::Observer {
public:
    Observer();

    virtual void update(const int &ticks) = 0;

};


#endif //PAC_MAN_OBSERVER_H
