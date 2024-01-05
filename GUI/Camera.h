//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_CAMERA_H
#define PAC_MAN_CAMERA_H
#include "iostream"
#include "../GUI/State.h"
/*
 * Class om coordinates correct door te geven
 */
class Coordinates{
    double xCoord;
    double yCoord;
public:
    Coordinates(double xCoord, double yCoord);

    [[nodiscard]] double getXCoord() const;

    [[nodiscard]] double getYCoord() const;

};

/*
 * Class die voor de berekening van alle pixel coordinates zorgt
 */
class GUI::Camera {
    int modelWidth;
    int modelHeight;
    int screenWidth;
    int screenHeight;
    static std::shared_ptr<GUI::Camera> cameraPointer;
public:
    virtual ~Camera();

    static std::shared_ptr<GUI::Camera> instance();

    /////////////////////////////////////////:
    // Getters and setters
    /////////////////////////////////////////:
    [[nodiscard]] int getModelWidth() const;

    void setModelWidth(int width);

    [[nodiscard]] int getModelHeight() const;

    void setModelHeight(int height);

    [[nodiscard]] Coordinates getCameraCoords(double row, double col) const;

    [[nodiscard]] int getScreenWidth() const;

    void setScreenWidth(int width);

    [[nodiscard]] int getScreenHeight() const;

    void setScreenHeight(int height);


protected:
    Camera();

};


#endif //PAC_MAN_CAMERA_H
