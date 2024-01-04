//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIWALL_H
#define PAC_MAN_GUIWALL_H
#include "EntityView.h"

class GUI::Wall: public GUI::EntityView {
    std::weak_ptr<Model::World> world;
    bool wallUpdated;
public:
    Wall(const std::shared_ptr<Model::EntityModel> &subject, const std::weak_ptr<Model::World> &world);

    /*
     * Functie wordt opgeroepen na het bouwen van de wereld om de muren er aan te passen op basis van de omringende muren:
     */
    void updateWall();

    void update(const double &ticks) override;

    ~Wall() override;

    [[nodiscard]] const std::weak_ptr<Model::World> &getWorld() const;

    [[nodiscard]] bool isWallUpdated() const;

    void setWallUpdated(bool updated);
};


#endif //PAC_MAN_GUIWALL_H
