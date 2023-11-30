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
    std::vector<Model::Observer*> observers;
public:
    EntityModel(int row, int col);

    [[nodiscard]] const std::string &getTag() const;

    void setTag(const std::string &tg);

    [[nodiscard]] bool isConsumed() const override;

    void consume();

    void addObserver(Model::Observer* observer);

    [[nodiscard]] const std::vector<Model::Observer *> &getObservers() const;
};


#endif //PAC_MAN_ENTITYMODEL_H
