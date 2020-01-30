#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QVector3D>
#include <QTime>
#include "camera/camerafree.h"
#include "camera/cameraorign.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget( QWidget* parent = 0 );
    ~GLWidget();

    float getT();
    void setT(float t);
    void setKeyPressText(QString s);
    void rotateBy(int xAngle, int yAngle, int zAngle);

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();

    Camera *camera = new CameraFree(QVector3D(0.0f, 0.0f, 20.0f), QVector3D(0.0f, 1.0f, 0.0f), QVector3D(0.0f,0.0f,-1.0f));
//    Camera *camera = new CameraFree(QVector3D(0.0f, 0.0f, 20.0f), QVector3D(1.0f,0.0f,0.0f));
//    CameraO camera = CameraO(QVector3D(10.0f, 14.14f, 10.0f), QVector3D(0.0f, 1.0f, 0.0f), QVector3D(-1.0f,-1.414f,-1.0f));
//    Camera *camera = new CameraOrigin(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f, 20.0f));
    QVector3D object_position = QVector3D(0,0,0);
    float rotate = 0; // 旋转角度
    float T = 3.0f;   // 旋转周期（秒）
    float deltaTime;  // 每帧延时
    QMatrix4x4 MVP;   // 变换矩阵
    QTime t;          // 帧计时器
    bool change = false;
    QString keyPressText;

private:
    bool prepareShaderProgram( const QString& vertexShaderPath, const QString& fragmentShaderPath );
    void getMVP(bool isStatic);

    QPoint lastPos;
    QGLShaderProgram m_shader;
    QGLBuffer m_vertexBuffer;
    QGLBuffer m_colorBuffer;
    QGLBuffer m_textureBuffer;
    QOpenGLTexture *myTexture;

//    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void render();
};

#endif // GLWIDGET_H
