//
// Created by Samuel on 03/01/2024.
//

#ifndef PAC_MAN_DIJKSTRAPOINT_H
#define PAC_MAN_DIJKSTRAPOINT_H
#include "Subject.h"


class Model::DijkstraPoint{
    int x;
    int y;
    std::vector<std::unique_ptr<DijkstraTransition>> transitions;
    bool explored;
public:
    DijkstraPoint(int x, int y);

    void addTransition(std::unique_ptr<DijkstraTransition> transition);

    bool canGoTo(const std::weak_ptr<DijkstraPoint>& dijkstraPoint);

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    [[nodiscard]] bool isExplored() const;

    void setExplored(bool b);
};


#endif //PAC_MAN_DIJKSTRAPOINT_H
