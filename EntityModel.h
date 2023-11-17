//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYMODEL_H
#define PAC_MAN_ENTITYMODEL_H
#include "Subject.h"

class EntityModel: public Subject{
    int row;
    int col;
    string tag;
public:
    EntityModel(int row, int col);

    [[nodiscard]] int getRow() const;

    void setPosX(int x);

    [[nodiscard]] int getCol() const;

    void setPosY(int y);

    [[nodiscard]] const string &getTag() const;

    void setTag(const string &tg);
};


#endif //PAC_MAN_ENTITYMODEL_H
