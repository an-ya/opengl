#ifndef CAMERAORIGN_H
#define CAMERAORIGN_H

#include "camera.h"
#include <QVector3D>
#include <QtMath>

class CameraOrigin : public Camera
{
public:
    float R = 10.0f;
    QVector3D Front;
    QVector3D WorldUp;
    QVector3D LookPosition;

    float xRot = 0.0f;
    float yRot = 0.0f;
    float zRot = 0.0f;

    float MouseSensitivity = 0.2f;

    CameraOrigin(QVector3D lookPosition, QVector3D cameraPosition, QVector3D worldUp = QVector3D(0.0f, 1.0f, 0.0f));

    QMatrix4x4 GetViewMatrix() override;
    void ProcessKeyboard(int direction, float deltaTime) override;
    void ProcessMouseMovement(float xoffset, float yoffset, float zoffset) override;

private:
    float GetVectorIncludedAngle(QVector3D a, QVector3D b);
    void updateCameraVectors();
};

#endif // CAMERAORIGN_H
