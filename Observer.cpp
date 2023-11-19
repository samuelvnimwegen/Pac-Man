//
// Created by Samuel on 16/11/2023.
//

#include "Observer.h"

Observer::Observer(Subject *subject) : subject(subject) {}

Subject *Observer::getSubject() const {
    return subject;
}

void Observer::setSubject(Subject *subj) {
    Observer::subject = subj;
}
