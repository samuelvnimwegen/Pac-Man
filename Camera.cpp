//
// Created by Samuel on 16/11/2023.
//

#include "Camera.h"




pair<float, float> Camera::getCameraCoords(int row, int col) const {
    float height = float(row) / float(modelHeight) * 2 - 1;
    float width = float(col) / float(modelWidth) * 2 - 1;
    return make_pair(height, width);
}

Camera::Camera(int modelWidth, int modelHeight) : modelWidth(modelWidth), modelHeight(modelHeight) {}


