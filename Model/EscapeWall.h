//
// Created by Samuel on 03/01/2024.
//

#ifndef PAC_MAN_ESCAPEWALL_H
#define PAC_MAN_ESCAPEWALL_H
#include "Wall.h"

class Model::EscapeWall: public Model::Wall{
public:
    EscapeWall(int row, int col);

    void update(const double &seconds) override;
};


#endif //PAC_MAN_ESCAPEWALL_H
