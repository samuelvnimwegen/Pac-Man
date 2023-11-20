//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_SUBJECT_H
#define PAC_MAN_SUBJECT_H
#include "iostream"
#include "vector"
using namespace std;

class Subject {
public:
    int row;
    int col;
    double cameraX;
    double cameraY;
    Subject(int row, int col);

    [[nodiscard]] double getCameraX() const;

    void setCameraX(double x);

    [[nodiscard]] double getCameraY() const;

    void setCameraY(double y);

    [[nodiscard]] int getRow() const;

    void setRow(int row);

    [[nodiscard]] virtual bool isConsumed() const = 0;

    [[nodiscard]] int getCol() const;

    void setCol(int c);
};


#endif //PAC_MAN_SUBJECT_H
