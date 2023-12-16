//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_CAMERA_H
#define PAC_MAN_CAMERA_H
#include "iostream"
#include "Subject.h"

class Coordinates{
    double xCoord;
    double yCoord;
public:
    Coordinates(double xCoord, double yCoord);

    [[nodiscard]] double getXCoord() const;

    [[nodiscard]] double getYCoord() const;

};
class GUI::Camera {
    int modelWidth;
    int modelHeight;
    double xSpeed;
    double ySpeed;
    static std::shared_ptr<GUI::Camera> cameraPointer;
public:
    virtual ~Camera();

    static std::shared_ptr<GUI::Camera> instance();

    [[nodiscard]] int getModelWidth() const;

    void setModelWidth(int width);

    [[nodiscard]] int getModelHeight() const;

    void setModelHeight(int height);

    [[nodiscard]] Coordinates getCameraCoords(int row, int col) const;

    [[nodiscard]] double getXSpeed() const;

    void setXSpeed(double speed);

    [[nodiscard]] double getYSpeed() const;

    void setYSpeed(double speed);

protected:
    Camera();

};


#endif //PAC_MAN_CAMERA_H
