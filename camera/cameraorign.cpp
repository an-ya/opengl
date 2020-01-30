#include "camera/cameraorign.h"
#include <QVector4D>

CameraOrigin::CameraOrigin(QVector3D lookPosition, QVector3D cameraPosition, QVector3D worldUp)
{
    R = lookPosition.distanceToPoint(cameraPosition);
    LookPosition = lookPosition;
    WorldUp = QVector3D(0.0f, 1.0f, 0.0f);

    QVector3D cameraPositionXZ = cameraPosition;
    cameraPositionXZ.setY(0.0f);
    QVector3D cameraPositionZ = cameraPositionXZ;
    cameraPositionZ.setX(0.0f);

    xRot = GetVectorIncludedAngle(cameraPosition, cameraPositionXZ);
    yRot = GetVectorIncludedAngle(cameraPositionXZ, cameraPositionZ);
    zRot = -GetVectorIncludedAngle(worldUp, WorldUp);

    updateCameraVectors();
}

QMatrix4x4 CameraOrigin::GetViewMatrix()
{   
    QMatrix4x4 matrix;
    matrix.lookAt(LookPosition - R * Front, LookPosition, WorldUp);
    matrix.rotate(zRot, Front);

    return matrix;
}

void CameraOrigin::ProcessKeyboard(int direction, float deltaTime)
{

}

void CameraOrigin::ProcessMouseMovement(float xoffset, float yoffset, float zoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    zoffset *= MouseSensitivity;

    yRot -= xoffset;
    xRot -= yoffset;
    zRot -= zoffset;

    if (xRot > 89.0f)
        xRot = 89.0f;
    if (xRot < -89.0f)
        xRot = -89.0f;

    updateCameraVectors();
}

float CameraOrigin::GetVectorIncludedAngle(QVector3D a, QVector3D b)
{
    return qRadiansToDegrees(acos(QVector3D::dotProduct(a, b) / (a.length() * b.length())));
}

void CameraOrigin::updateCameraVectors()
{
    float rx = qDegreesToRadians(xRot);
    float ry = qDegreesToRadians(yRot);
    Front = -QVector3D(cos(rx) * sin(ry), sin(rx), cos(rx) * cos(ry));
}
