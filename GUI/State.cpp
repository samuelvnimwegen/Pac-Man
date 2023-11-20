//
// Created by Samuel on 16/11/2023.
//

#include "State.h"

const string &State::getTag() const {
    return tag;
}

void State::setTag(const string &tag) {
    State::tag = tag;
}

State::State() {}

State::~State() {

}
