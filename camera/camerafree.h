#ifndef CAMERAFREE_H
#define CAMERAFREE_H

#include "camera.h"
#include <QVector3D>
#include <QtMath>
#include <QQuaternion>

class CameraFree : public Camera
{
public:
    QVector3D Position;
    QVector3D Front;
    QVector3D Up;
    QVector3D Right;
    QVector3D WorldUp;
    QQuaternion Q = QQuaternion();
    QQuaternion Qr = QQuaternion();

    QVector3D Z = QVector3D(0.0f, 0.0f, 1.0f);
    QVector3D Y = QVector3D(0.0f, 1.0f, 0.0f);
    QVector3D X = QVector3D(1.0f, 0.0f, 0.0f);

    float Yaw = 0.0f;
    float Pitch = 0.0f;
    float Roll = 0.0f;

    float MovementSpeed = 2.5f;
    float MouseSensitivity = 0.05f;

    CameraFree(QVector3D position, QVector3D worldup = QVector3D(0.0f,1.0f,0.0f), QVector3D front = QVector3D(0.0f,0.0f,-1.0f));

    QMatrix4x4 GetViewMatrix() override;
    void ProcessKeyboard(int direction, float deltaTime) override;
    void ProcessMouseMovement(float xoffset, float yoffset, float zoffset) override;

private:
    void updateVectors();
    float GetVectorIncludedAngle(QVector3D a, QVector3D b);
    QQuaternion RotationBetweenVectors(QVector3D start, QVector3D dest);
    QVector3D rotateVector(float degrees, QVector3D k, QVector3D v);
};

#endif // CAMERAFREE_H
