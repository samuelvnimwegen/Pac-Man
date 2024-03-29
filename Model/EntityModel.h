//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYMODEL_H
#define PAC_MAN_ENTITYMODEL_H
#include "Subject.h"
#include "memory"
class Model::EntityModel: public  Model::Subject{
    entityTag tag;
    double row;
    double col;
public:
    EntityModel(int row, int col);

    virtual void update(const double &seconds) = 0;

    [[nodiscard]] entityTag getTag() const;

    void setTag(entityTag entityTag);

    [[nodiscard]] double getY() const;

    [[nodiscard]] double getX() const;

    void setY(double r);

    void setX(double c);
};

int toTile(double db);


#endif //PAC_MAN_ENTITYMODEL_H
