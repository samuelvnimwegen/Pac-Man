//
// Created by Samuel on 03/01/2024.
//

#ifndef PAC_MAN_DIJKSTRATRANSITION_H
#define PAC_MAN_DIJKSTRATRANSITION_H
#include "Subject.h"

class Model::DijkstraTransition{
    std::weak_ptr<DijkstraPoint> nextPoint;
public:
    explicit DijkstraTransition(const std::weak_ptr<DijkstraPoint> &nextPoint);

    [[nodiscard]] const std::weak_ptr<DijkstraPoint> &getNextPoint() const;
};


#endif //PAC_MAN_DIJKSTRATRANSITION_H
