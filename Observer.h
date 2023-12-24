//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H
#include "Subject.h"

class Model::Observer {
public:
    Observer();

    virtual void update(const double &seconds) = 0;

    virtual void collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) = 0;
};


#endif //PAC_MAN_OBSERVER_H
