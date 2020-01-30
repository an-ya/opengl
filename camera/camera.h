#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QMatrix3x3>

class Camera
{
public:
    float zoom = 45.0f;
    float Zoom = 45.0f;
    float dZoom = 0.0f;
    float ScrollSensitivity = 0.015f;
    enum Camera_Movement {
        FORWARD = 1,
        BACKWARD,
        LEFT,
        RIGHT
    };

    float getZoom(float deltaTime);
    void ProcessMouseScroll(float yoffset);
    virtual QMatrix4x4 GetViewMatrix() = 0;
    virtual void ProcessKeyboard(int direction, float deltaTime) = 0;
    virtual void ProcessMouseMovement(float xoffset, float yoffset, float zoffset) = 0;
};

#endif // CAMERA_H
