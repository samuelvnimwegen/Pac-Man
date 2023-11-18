//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYVIEW_H
#define PAC_MAN_ENTITYVIEW_H
#include "../Observer.h"
#include "SFML/Graphics.hpp"

class EntityView: public Observer{
    int col;
    int row;
public:
    explicit EntityView(Subject *subject);

    virtual string getSpriteFileName();
};


#endif //PAC_MAN_ENTITYVIEW_H
