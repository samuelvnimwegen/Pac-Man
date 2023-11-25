//
// Created by Samuel on 16/11/2023.
//

#include "Camera.h"
using namespace std;

GUI::Camera* GUI::Camera::cameraPointer = nullptr;



pair<float, float> GUI::Camera::getCameraCoords(int row, int col) const {
    float height = float(row) / float(modelHeight) * 2 - 1;
    float width = float(col) / float(modelWidth) * 2 - 1;
    return make_pair(height, width);
}

GUI::Camera *GUI::Camera::instance() {
    if (cameraPointer == nullptr){
        cameraPointer = new GUI::Camera();
        return cameraPointer;
    }
}

int GUI::Camera::getModelWidth() const {
    return modelWidth;
}

void GUI::Camera::setModelWidth(int width) {
    Camera::modelWidth = width;
}

int GUI::Camera::getModelHeight() const {
    return modelHeight;
}

void GUI::Camera::setModelHeight(int height) {
    Camera::modelHeight = height;
}

GUI::Camera::Camera(){
    this->modelWidth = 0;
    this->modelHeight = 0;
};

GUI::Camera::~Camera() = default;


