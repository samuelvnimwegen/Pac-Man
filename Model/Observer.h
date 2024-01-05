//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H
#include "Subject.h"

class Model::Observer {
public:
    Observer();

    /*
     * Update de observers
     */
    virtual void update(const double &nanoSeconds) = 0;

    /*
     * Als er een collectable wordt collected wordt deze hier doorgegeven
     */
    virtual void collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) = 0;

    /*
     * Wordt gebruikt als het level op pauze wordt gezet of in een animatie zit
     */
    virtual void levelHalt() = 0;

    /*
     * Als PacMan sterft wordt deze functie opgeroepen
     */
    virtual void pacManDied() = 0;

    /*
     * Als er een ghost wordt opgegeten wordt dit opgeroepen
     */
    virtual void ghostEaten() = 0;

    /*
     * Als de game wordt restarted en dus de game voorbij is
     */
    virtual void restartGame() = 0;

    /*
     * Wordt opgeroepen bij het gaan naar het volgende level
     */
    virtual void nextLevel() = 0;
};


#endif //PAC_MAN_OBSERVER_H
