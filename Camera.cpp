//
// Created by Samuel on 16/11/2023.
//

#include "Camera.h"
using namespace std;

GUI::Camera* GUI::Camera::cameraPointer = nullptr;



Coordinates GUI::Camera::getCameraCoords(int row, int col) const {
    double height = double (row) / double(modelHeight) * 2 - 1;
    double width = double(col) / double(modelWidth) * 2 - 1;
    return {width, height};
}

GUI::Camera *GUI::Camera::instance() {
    if (cameraPointer == nullptr){
        cameraPointer = new GUI::Camera();
        return cameraPointer;
    }
    return cameraPointer;
}

int GUI::Camera::getModelWidth() const {
    return modelWidth;
}

void GUI::Camera::setModelWidth(int width) {
    if (this->getModelWidth() != 0){
        xSpeed =  double(1) / double(this->getModelWidth()) / 100;
    }
    Camera::modelWidth = width;
}

int GUI::Camera::getModelHeight() const {
    return modelHeight;
}

void GUI::Camera::setModelHeight(int height) {
    if (this->getModelHeight() != 0){
        ySpeed =  double(1) / double(this->getModelHeight()) / 100;
    }
    Camera::modelHeight = height;
}

GUI::Camera::Camera(){
    modelWidth = 0;
    modelHeight = 0;
    xSpeed = 0;
    ySpeed = 0;
}

double GUI::Camera::getXSpeed() const {
    return xSpeed;
}

void GUI::Camera::setXSpeed(double speed) {
    Camera::xSpeed = speed;
}

double GUI::Camera::getYSpeed() const {
    return ySpeed;
}

void GUI::Camera::setYSpeed(double speed) {
    Camera::ySpeed = speed;
}


GUI::Camera::~Camera() = default;


Coordinates::Coordinates(double xCoord, double yCoord) : xCoord(xCoord), yCoord(yCoord) {}

double Coordinates::getXCoord() const {
    return xCoord;
}


double Coordinates::getYCoord() const {
    return yCoord;
}

