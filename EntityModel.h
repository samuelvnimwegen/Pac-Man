//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYMODEL_H
#define PAC_MAN_ENTITYMODEL_H
#include "Subject.h"
#include "memory"
class Model::EntityModel: public  Model::Subject{
    std::string tag;
    bool consumed;
    int row;
    int col;
public:
    EntityModel(int row, int col);

    [[nodiscard]] const std::string &getTag() const;

    void setTag(const std::string &tg);

    [[nodiscard]] bool isConsumed() const;

    void consume();

    [[nodiscard]] int getRow() const;

    [[nodiscard]] int getCol() const;

    void setConsumed(bool cons);

    void setRow(int r);

    void setCol(int c);
};


#endif //PAC_MAN_ENTITYMODEL_H
