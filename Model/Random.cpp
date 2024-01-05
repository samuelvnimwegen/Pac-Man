//
// Created by Samuel on 16/11/2023.
//

#include "Random.h"

std::shared_ptr<Model::Random> Model::Random::m_pRandom = nullptr;

Model::Random::Random(): mersenneTwister(std::random_device{}()) {
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

template<typename T>
void randomSort(std::vector<T> &vector) {
    std::vector<T> copy = vector;
    std::vector<T> sorted;
    while (!copy.empty()){
        auto number = Model::Random::instance()->getRandomInt(0, copy.size() - 1);
        sorted.push_back(copy.at(number));
        copy.erase(copy.begin() + number);
    }
    vector = sorted;
}

template void randomSort<int>(std::vector<int> &vector);
template void randomSort<direction>(std::vector<direction> &vector);
template void randomSort<std::pair<int,int>>(std::vector<std::pair<int,int>> &vector);