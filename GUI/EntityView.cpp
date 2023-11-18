//
// Created by Samuel on 16/11/2023.
//

#include "EntityView.h"


string EntityView::getSpriteFileName() {
    return "Sprites/Error.png";
}

EntityView::EntityView(Subject *subject) : Observer(subject) {
    col = subject->col;
    row = subject->row;
}

