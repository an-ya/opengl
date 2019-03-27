#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>
#include <QTime>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget( QWidget* parent = 0 );
    ~GLWidget();

    float getT();
    void setT(float t);

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();

    QVector3D position = QVector3D(5,5,10); // 镜头初始位置
    QVector3D direction = QVector3D(0,0,0);
    float rotate = 0; // 旋转角度
    float T = 3.0f;   // 旋转周期（秒）
    QMatrix4x4 MVP; // 变换矩阵
    QTime t; //帧计时器
    bool change = false;
    bool keyPress = false;
    QString keyPressText;
private:
    bool prepareShaderProgram( const QString& vertexShaderPath, const QString& fragmentShaderPath );
    void getMVP();
//    void keyPressEvent(QKeyEvent * event);
//    void keyReleaseEvent(QKeyEvent *event);

    QGLShaderProgram m_shader;
    QGLBuffer m_vertexBuffer;

private slots:
    void render();
};

#endif // GLWIDGET_H
