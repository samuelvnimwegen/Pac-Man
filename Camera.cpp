//
// Created by Samuel on 16/11/2023.
//

#include "Camera.h"
using namespace std;

std::shared_ptr<GUI::Camera> GUI::Camera::cameraPointer = nullptr;


Coordinates GUI::Camera::getCameraCoords(double row, double col) const {
    double height = double (row) / double(this->getModelHeight()) * 2 - 1;
    double width = double(col) / double(this->getModelWidth()) * 2 - 1;
    return {width, height};
}

std::shared_ptr<GUI::Camera> GUI::Camera::instance() {
    if (cameraPointer == nullptr){
        cameraPointer = shared_ptr<GUI::Camera>(new GUI::Camera());
        return cameraPointer;
    }
    return cameraPointer;
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
    screenHeight = 0;
    screenWidth = 0;
    modelWidth = 0;
    modelHeight = 0;
}

int GUI::Camera::getScreenWidth() const {
    return screenWidth;
}

void GUI::Camera::setScreenWidth(int width) {
    Camera::screenWidth = width;
}

int GUI::Camera::getScreenHeight() const {
    return screenHeight;
}

void GUI::Camera::setScreenHeight(int height) {
    Camera::screenHeight = height;
}


GUI::Camera::~Camera() = default;


Coordinates::Coordinates(double xCoord, double yCoord) : xCoord(xCoord), yCoord(yCoord) {}

double Coordinates::getXCoord() const {
    return xCoord;
}


double Coordinates::getYCoord() const {
    return yCoord;
}

