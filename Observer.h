//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H
#include "World.h"

class Observer {
public:
    Observer();

    [[nodiscard]] virtual Subject *getSubject() const = 0;
};


#endif //PAC_MAN_OBSERVER_H
