//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIWALL_H
#define PAC_MAN_GUIWALL_H
#include "EntityView.h"

class GUIWall: public EntityView {
public:
    GUIWall(World *world, int posX, int posY);
public:
    string getSpriteFileName() override;
};


#endif //PAC_MAN_GUIWALL_H
