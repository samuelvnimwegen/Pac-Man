//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_ENTITYMODEL_H
#define PAC_MAN_ENTITYMODEL_H
#include "Subject.h"

class EntityModel: public Subject{
    string tag;
    bool consumed;
public:
    EntityModel(int row, int col);

    void setPosX(int x);

    void setPosY(int y);

    [[nodiscard]] const string &getTag() const;

    void setTag(const string &tg);

    [[nodiscard]] bool isConsumed() const override;

    void consume();
};


#endif //PAC_MAN_ENTITYMODEL_H
