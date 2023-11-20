//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STATE_H
#define PAC_MAN_STATE_H
#include "iostream"
#include "vector"
using namespace std;

class State {
    string tag;
public:
    State();

    virtual ~State();

    [[nodiscard]] const string &getTag() const;

    void setTag(const string &tag);

    virtual State* getNext() = 0;
};


#endif //PAC_MAN_STATE_H
