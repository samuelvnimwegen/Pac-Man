//
// Created by Samuel on 16/11/2023.
//

#include "State.h"

const string &GUI::State::getTag() const {
    return tag;
}

void GUI::State::setTag(const string &tag) {
    State::tag = tag;
}

GUI::State::State() {}

GUI::State::~State() {

}
