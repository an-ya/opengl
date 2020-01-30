#include "camera/camerafree.h"

CameraFree::CameraFree(QVector3D position, QVector3D worldup, QVector3D front)
{
    Position = position;
    WorldUp = worldup;
    Front = front;
    Right = QVector3D::crossProduct(Front, WorldUp);
    Up    = QVector3D::crossProduct(Right, Front);

//    QQuaternion q1 = QQuaternion::fromAxes(Right, Up, -Front);

    QQuaternion q1 = QQuaternion::rotationTo(Z, -Front);
    QVector3D newUp = q1.rotatedVector(Y);
    QQuaternion q2 = QQuaternion::rotationTo(newUp, Up);
//    q1 = q1.conjugated();
//    q2 = q2.conjugated();

    QQuaternion temp = q2 * q1;

    QVector3D euler = temp.toEulerAngles();
    qWarning() << euler;

//    temp = temp.conjugated();
//    Pitch = 6;
//    QQuaternion temp = QQuaternion::fromAxisAndAngle(Y, 6);

//    Qf = temp;
//    Qr = temp;
//    Q = temp;
//    Qr = Q;
//    X = Right;
//    Y = Up;
//    Z = -Front;

//    QVector3D FrontXZ = Front;
//    FrontXZ.setY(0.0f);
//    QVector3D FrontYZ = Front;
//    FrontYZ.setX(0.0f);

//    Yaw = GetVectorIncludedAngle(FrontXZ, -Z);
//    Pitch = GetVectorIncludedAngle(FrontYZ, -Z);

    Pitch = -euler.x();
    Yaw = -euler.y();
    Roll = -euler.z();


//    QQuaternion rp = QQuaternion::fromAxisAndAngle(X, Pitch);
//    Y = rp.rotatedVector(QVector3D(0.0f, 1.0f, 0.0f));
//    QQuaternion ry = QQuaternion::fromAxisAndAngle(Y, Yaw);
//    QQuaternion rr = QQuaternion::fromAxisAndAngle(Z, Roll);

//    Q = ry * rp;
//    Q = QQuaternion::fromEulerAngles(Pitch, Yaw, 0.0f);

//    Right = QVector3D::crossProduct(Front, WorldUp);
//    Up    = QVector3D::crossProduct(Right, Front);
//    qWarning() << WorldUp;
//    qWarning() << Front << ", " << Right << ", " << Up;
//    Q = QQuaternion();
//    updateVectors();
}

QMatrix4x4 CameraFree::GetViewMatrix()
{
    QMatrix4x4 matrix;
//    matrix.rotate(Roll, Front);
//    matrix.translate(Position);
//    matrix.rotate(Qr);
    matrix.rotate(Q);
//    matrix.lookAt(QVector3D(0.0f, 0.0f, 20.0f), QVector3D(6.0f, 6.0f, -1.0f), QVector3D(0.0f, 1.0f, 0.0f));


    matrix.translate(-Position);


//    QMatrix4x4 test;
//    test.lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f) + Z, Y);
//    qWarning() << test;
//    matrix.rotate(180.0f, Z);
//    matrix.translate(-Position);



//    matrix.lookAt(Position, Position + Front, WorldUp);
//    matrix.rotate(Q);

//    matrix.rotate(Yaw, Y);
//    matrix.rotate(Pitch, X);
//    matrix.rotate(Roll, Front);

//    matrix.rotate(Q);
//    matrix.rotate(Q);
    return matrix;
}

void CameraFree::ProcessKeyboard(int direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
//    qWarning() << Front << "," << Right;
//    qWarning() << Position;
}

void CameraFree::ProcessMouseMovement(float xoffset, float yoffset, float zoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= -MouseSensitivity;
    zoffset *= MouseSensitivity;

    Pitch += yoffset;
    Yaw   += xoffset;
    Roll  += zoffset;

    QQuaternion x = QQuaternion::fromAxisAndAngle(X, Pitch);
    QQuaternion y = QQuaternion::fromAxisAndAngle(Y, Yaw);
    QQuaternion z = QQuaternion::fromAxisAndAngle(Z, Roll);

    Q = x * z * y;

//    QQuaternion x = QQuaternion::fromAxisAndAngle(X, yoffset);
//    QQuaternion y = QQuaternion::fromAxisAndAngle(Y, xoffset);
//    QQuaternion z = QQuaternion::fromAxisAndAngle(Z, zoffset);

//    if (zoffset == 0) {
//        Pitch += yoffset;
//        Yaw   += xoffset;
//        QQuaternion rp = QQuaternion::fromAxisAndAngle(X, Pitch);
//        QQuaternion ry = QQuaternion::fromAxisAndAngle(Y, Yaw);
//        Q = ry * rp * Qr;
//    } else {
//        if (xoffset == 0 && yoffset == 0) {
//            Q = z * Q;
//        } else {
//            Q = z * x * y * Q;
//        }
//        Qr = Q;
//        Pitch = 0.0f;
//        Yaw   = 0.0f;
//    }

    QQuaternion QConjugate = Q.conjugated();
    Front = -QConjugate.rotatedVector(Z);
    Right = QConjugate.rotatedVector(X);

//    qWarning() << Right << ", " << Front;

//    updateVectors();


//    QQuaternion base = Qp * Qy;
//    Front = base.rotatedVector(Front);
//    qWarning() << Front;
//    Right = QVector3D::crossProduct(Front, WorldUp);
//    if (zoffset != 0) {

//    }

//    if (xoffset != 0) {
//        Front = rotateVector(xoffset, Up, Front);
//        Right = QVector3D::crossProduct(Front, Up);
//    }
//    if (yoffset != 0) {
//        Front = rotateVector(yoffset, Right, Front);
//        Up    = QVector3D::crossProduct(Right, Front);
//    }
//    if (zoffset != 0) {
//        Right = rotateVector(zoffset, Front, Right);
//        Up    = rotateVector(zoffset, Front, Up);
//    }

//    qWarning() << Up << ", " << Front;


//    if (Pitch > 89.0f)
//        Pitch = 89.0f;
//    if (Pitch < -89.0f)
//        Pitch = -89.0f;



//    updateCameraVectors();
}

void CameraFree::updateVectors()
{
//    Front = QVector3D(
//                qCos(qDegreesToRadians(Yaw)) * qCos(qDegreesToRadians(Pitch)),
//                qSin(qDegreesToRadians(Pitch)),
//                qSin(qDegreesToRadians(Yaw)) * qCos(qDegreesToRadians(Pitch))
//                );
//    QQuaternion Qp = QQuaternion(cos(qDegreesToRadians(Pitch) / 2.0f), sin(qDegreesToRadians(Pitch) / 2.0f) * X);
//    QQuaternion Qy = QQuaternion(cos(qDegreesToRadians(Yaw) / 2.0f), sin(qDegreesToRadians(Yaw) / 2.0f) * Y);
    QQuaternion Qp = QQuaternion::fromAxisAndAngle(X, Pitch);
    QQuaternion Qy = QQuaternion::fromAxisAndAngle(Y, Yaw);

//    qWarning() << Pitch << "," << Yaw;
    QQuaternion base = Qp * Qy;
    Q = base;
//    Front = Z;
//    Front = Q.rotatedVector(-Z);
//    qWarning() << Front;
//    Right = QVector3D::crossProduct(Front, WorldUp);



//    Q = QQuaternion::rotationTo(Z, Front);
//    Q = QQuaternion::fromEulerAngles(Pitch, Yaw, Roll);
//    QQuaternion Qp = QQuaternion(Pitch / 360.0f, X);
//    QQuaternion Qy = QQuaternion(Yaw / 360.0f, Y);

//    QQuaternion base = Qp * Qy;
//    Front = base.rotatedVector(Z);


//    QQuaternion Qr = QQuaternion(Roll / 360.0f, Z);

//    qWarning() << Front;
//    QQuaternion Qr = QQuaternion(Roll / 360.0f, Z);

//    Q = Qp * Qy * Qr;
//    Q.normalize();

//    Right = QVector3D::crossProduct(Z, WorldUp);
//    Right = Qr.rotatedVector(Right);

//    Front = Q.rotatedVector(Z);
//    Right = QVector3D::crossProduct(Front, WorldUp);
//    qWarning() << Q;
//    Right = QVector3D::crossProduct(Front, WorldUp);
//    Front = rotateVector(Pitch, X, Z);
//    Front = rotateVector(Yaw, Y, Front);
//    Right = QVector3D::crossProduct(Front, WorldUp);
//    Right = rotateVector(Roll, Front, Right);

//    Right = rotateVector(Yaw, QVector3D(0.0f, 1.0f, 0.0f), Right);
//    Right = rotateVector(Roll, QVector3D(0.0f, 0.0f, -1.0f), Right);
//    Front = QVector3D(
//                qCos(qDegreesToRadians(Yaw)) * qCos(qDegreesToRadians(Pitch)),
//                qSin(qDegreesToRadians(Pitch)),
//                qSin(qDegreesToRadians(Yaw)) * qCos(qDegreesToRadians(Pitch))
//                );

//    Front = Q.rotatedVector(Front);
//    Right = QVector3D::crossProduct(Front, WorldUp);
//    Up    = QVector3D::crossProduct(Right, Front);
//    Right = -X;
//    Front = Z;
}

QVector3D CameraFree::rotateVector(float degrees, QVector3D k, QVector3D v)
{
    // 罗德里格旋转公式
//    float cos0 = cos(qDegreesToRadians(degrees));
//    float sin0 = sin(qDegreesToRadians(degrees));
//    float dp = QVector3D::dotProduct(k, v);
//    QVector3D cp = QVector3D::crossProduct(k, v);
//    QVector3D result = cos0 * v + (1 - cos0) * dp * k + sin0 * cp;
//    qWarning() << degrees;
//    return result.normalized();
    QMatrix4x4 matrix;
    matrix.rotate(degrees, k);
    QVector4D t = QVector4D(v, 0.0f);
    t = t * matrix;
    return t.toVector3D();
}

float CameraFree::GetVectorIncludedAngle(QVector3D a, QVector3D b)
{
    return qRadiansToDegrees(acos(QVector3D::dotProduct(a, b) / (a.length() * b.length())));
}

QQuaternion CameraFree::RotationBetweenVectors(QVector3D start, QVector3D dest) {
    start.normalize();
    dest.normalize();

    float cosTheta = QVector3D::dotProduct(start, dest);
    QVector3D rotationAxis;

//    if (cosTheta < -1 + 0.001f){
//        rotationAxis = QVector3D::crossProduct(QVector3D(0.0f, 0.0f, 1.0f), start);
//        if (rotationAxis.length() < 0.01 )
//            rotationAxis = QVector3D::crossProduct(QVector3D(1.0f, 0.0f, 0.0f), start);

//        rotationAxis.normalize();
//        qWarning() << QQuaternion(0.5f , rotationAxis);
//        return QQuaternion(0.5f , rotationAxis);
//    }

    // Implementation from Stan Melax's Game Programming Gems 1 article
    rotationAxis = QVector3D::crossProduct(start, dest);

    float s = sqrt( (1+cosTheta)*2 );
    float invs = 1 / s;

    qWarning() << s << "," << invs;
    qWarning() << QQuaternion(
                      s * 0.5f,
                      rotationAxis.x() * invs,
                      rotationAxis.y() * invs,
                      rotationAxis.z() * invs
                  );

    return QQuaternion(
        s * 0.5f,
        rotationAxis.x() * invs,
        rotationAxis.y() * invs,
        rotationAxis.z() * invs
    );
}
