//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_MENUSTATE_H
#define PAC_MAN_MENUSTATE_H
#include "State.h"
#include "LevelState.h"
class GUI::MenuState: public GUI::State{
public:
    MenuState();

    LevelState* getNext() override;

    ~MenuState() override;


};


#endif //PAC_MAN_MENUSTATE_H
