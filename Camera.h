//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_CAMERA_H
#define PAC_MAN_CAMERA_H
#include "iostream"
using namespace std;

class Camera {
    int modelWidth;
    int modelHeight;
public:
    Camera(int modelWidth, int modelHeight);

    [[nodiscard]] pair<float,float> getCameraCoords(int row, int col) const;
};


#endif //PAC_MAN_CAMERA_H
