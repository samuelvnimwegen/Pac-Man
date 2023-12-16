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
    std::vector<std::shared_ptr<Model::Observer>> observers;
public:
    EntityModel(int row, int col);

    [[nodiscard]] const std::string &getTag() const;

    void setTag(const std::string &tg);

    [[nodiscard]] bool isConsumed() const override;

    void consume();

    [[nodiscard]] const std::vector<std::shared_ptr<Model::Observer>> &getObservers() const;

    void addObserver(const std::shared_ptr<Model::Observer>& observer);
};


#endif //PAC_MAN_ENTITYMODEL_H
