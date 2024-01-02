//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_RANDOM_H
#define PAC_MAN_RANDOM_H
#include "Subject.h"
#include "random"

class Model::Random {
    std::mt19937 mersenneTwister;
    static std::shared_ptr<Model::Random> m_pRandom;
protected:
    explicit Random();
public:
    static std::shared_ptr<Model::Random> instance();

    Random(Model::Random &other) = delete;

    void operator=(const Model::Random&) = delete;

    int getRandomInt(const int &lowestVal, const int &highestVal);

    double getRandomDouble(const double &lowestVal, const double &highestVal);
};


#endif //PAC_MAN_RANDOM_H
