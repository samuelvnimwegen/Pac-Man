//
// Created by Samuel on 16/11/2023.
//

#include "Subject.h"




int Model::Subject::getRow() const {
    return row;

}

void Model::Subject::setRow(int r) {
    Subject::row = r;
}

int Model::Subject::getCol() const {
    return col;
}

void Model::Subject::setCol(int c) {
    Subject::col = c;
}

Model::Subject::Subject(int row, int col) : row(row), col(col) {}
