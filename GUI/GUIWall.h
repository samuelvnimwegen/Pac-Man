//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GUIWALL_H
#define PAC_MAN_GUIWALL_H
#include "EntityView.h"

class GUIWall: public EntityView {
    Wall* subject;
public:
    explicit GUIWall(Wall *subject);

    ~GUIWall() override;

    Subject * getSubject() const override;

};


#endif //PAC_MAN_GUIWALL_H
