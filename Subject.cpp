//
// Created by Samuel on 16/11/2023.
//

#include "Subject.h"



Subject::Subject(int row, int col) : row(row), col(col) {
    cameraX = 0;
    cameraY = 0;
}

double Subject::getCameraX() const {
    return cameraX;
}

void Subject::setCameraX(double x) {
    Subject::cameraX = x;
}

double Subject::getCameraY() const {
    return cameraY;
}

void Subject::setCameraY(double y) {
    Subject::cameraY = y;
}

int Subject::getRow() const {
    return row;

}

void Subject::setRow(int r) {
    Subject::row = r;
}

int Subject::getCol() const {
    return col;
}

void Subject::setCol(int c) {
    Subject::col = c;
}
