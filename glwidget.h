#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLBuffer>
#include <QGLShaderProgram>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget( QWidget* parent = 0 );
    ~GLWidget();

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();

private:
    bool prepareShaderProgram( const QString& vertexShaderPath, const QString& fragmentShaderPath );

    QGLShaderProgram m_shader;
    QGLBuffer m_vertexBuffer;
};

#endif // GLWIDGET_H
