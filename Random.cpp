//
// Created by Samuel on 16/11/2023.
//

#include "Random.h"

std::shared_ptr<Model::Random> Model::Random::m_pRandom = nullptr;

Model::Random::Random() {
    std::random_device rd;
    mersenneTwister = std::mt19937(rd());
}

std::shared_ptr<Model::Random> Model::Random::instance() {
    if (m_pRandom == nullptr){
        m_pRandom = std::shared_ptr<Model::Random>(new Random);
    }
    return m_pRandom;
}

int Model::Random::getRandomInt(const int &lowestVal, const int &highestVal) {
    auto distribution = std::uniform_int_distribution(lowestVal, highestVal);
    return distribution(mersenneTwister);
}

double Model::Random::getRandomDouble(const double &lowestVal, const double &highestVal) {
    auto distribution = std::uniform_real_distribution(lowestVal, highestVal);
    return distribution(mersenneTwister);
}
