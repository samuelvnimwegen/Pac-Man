//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIPACMAN_H
#define PAC_MAN_GUIPACMAN_H
#include "EntityView.h"
#include "iostream"

class GUI::GUIPacMan: public GUI::EntityView{
    std::weak_ptr<Model::PacMan> pacManModel;
    int textureNr;
    int deadTextureNr;
public:
    explicit GUIPacMan(const std::shared_ptr<Model::PacMan> &subject);

    ~GUIPacMan() override;

    void update(const double &ticks) override;

    void updateTextureNr();

    void updateSprite();

    [[nodiscard]] int getTextureNr() const;

    void setTextureNr(int nr);

    [[nodiscard]] std::shared_ptr<Model::PacMan> getPacManModel() const;

    int getDeadTextureNr() const;

    void setDeadTextureNr(int nr);
};


#endif //PAC_MAN_GUIPACMAN_H
