//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIWALL_H
#define PAC_MAN_GUIWALL_H
#include "EntityView.h"

class GUI::GUIWall: public GUI::EntityView {
public:
    explicit GUIWall(const std::shared_ptr<Model::Wall>& subject, std::weak_ptr<sf::RenderWindow> win);

    ~GUIWall() override;

};


#endif //PAC_MAN_GUIWALL_H
