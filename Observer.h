//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H
#include "World.h"

class Observer {
    Subject* subject;
public:
    explicit Observer(Subject *subject);

    Subject *getSubject() const;

    void setSubject(Subject *subj);
};


#endif //PAC_MAN_OBSERVER_H
