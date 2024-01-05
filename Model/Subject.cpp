//
// Created by Samuel on 16/11/2023.
//

#include "Subject.h"
using namespace std;




const vector<std::shared_ptr<Model::Observer>> &Model::Subject::getObservers() const {
    return observers;
}

void Model::Subject::addObserver(const std::shared_ptr<Model::Observer>& observer) {
    observers.push_back(observer);
}

Model::Subject::Subject() = default;

