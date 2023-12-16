//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIWALL_H
#define PAC_MAN_GUIWALL_H
#include "EntityView.h"

class GUI::GUIWall: public GUI::EntityView {
public:
    explicit GUIWall(std::shared_ptr<Model::Wall> subject);

    ~GUIWall() override;



};


#endif //PAC_MAN_GUIWALL_H
