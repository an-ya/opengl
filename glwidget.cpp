#include <QApplication>
#include <QCoreApplication>
#include <QSurfaceFormat>
#include <QKeyEvent>
#include <QVector3D>
#include <QVector4D>
#include <QDateTime>
#include <QOpenGLContext>
#include "windows.h"
#include "glwidget.h"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

GLWidget::GLWidget( QWidget* parent )
 : QOpenGLWidget( parent )
{
    QSurfaceFormat format;
    format.setSamples(4);

    setFormat(format);
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Enable MASS
    glEnable(GL_MULTISAMPLE);
    // Set the clear color to black
    glClearColor( 0.1171875f, 0.1171875f, 0.1171875f, 1.0f );

    // Prepare a complete shader program…
    if ( !prepareShaderProgram( ":/new/simple.vert", ":/new/simple.frag" ) )
        return;

    // We need us some vertex data. Start simple with a triangle ;-)
    float points[] = {
        -1.0f,-1.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,
        1.0f,-1.0f,0.0f,1.0f, 0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,1.0f, 0.0f,0.0f,1.0f
    };

    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QGLBuffer::StaticDraw );
    if ( !m_vertexBuffer.bind() )
    {
        qWarning() << "Could not bind vertex buffer to the context";
        return;
    }
    m_vertexBuffer.allocate( points, 3 * 7 * sizeof( float ) );

    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if ( !m_shader.bind() )
    {
        qWarning() << "Could not bind shader program to context";
        return;
    }

    // Enable the "vertex" attribute to bind it to our currently bound
    // vertex buffer.
    // (name,type,offset,tupleSize,stride)
    m_shader.setAttributeBuffer( "vertex", GL_FLOAT, 0 * sizeof( float ), 4, 7 * sizeof( float ));
    m_shader.enableAttributeArray( "vertex" );

    m_shader.setAttributeBuffer( "color", GL_FLOAT, 4 * sizeof( float ), 3, 7 * sizeof( float ));
    m_shader.enableAttributeArray( "color" );

//    int matrixLocation = m_shader.uniformLocation("MVP");
//    getMVP();
//    m_shader.setUniformValue(matrixLocation, MVP);
//    int vertexColorLocation = m_shader.uniformLocation("ourColor");
//    m_shader.setUniformValue(vertexColorLocation, QVector4D(0.0f, 1.0f, 0.0f, 1.0f));
}

bool GLWidget::prepareShaderProgram( const QString& vertexShaderPath,
 const QString& fragmentShaderPath )
{
    // First we load and compile the vertex shader…
    bool result = m_shader.addShaderFromSourceFile( QGLShader::Vertex, vertexShaderPath );
    if ( !result )
        qWarning() << m_shader.log();

    // …now the fragment shader…
    result = m_shader.addShaderFromSourceFile( QGLShader::Fragment, fragmentShaderPath );
    if ( !result )
        qWarning() << m_shader.log();

    // …and finally we link them to resolve any references.
    result = m_shader.link();
    if ( !result )
        qWarning() << "Could not link shader program:" << m_shader.log();

    return result;
}

void GLWidget::resizeGL( int w, int h )
{
    // Set the viewport to window dimensions
    glViewport( 0, 0, w, qMax( h, 1 ) );

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int matrixLocation = m_shader.uniformLocation("MVP");
    getMVP();
    m_shader.setUniformValue(matrixLocation, MVP);
//    int vertexColorLocation = m_shader.uniformLocation("ourColor");
//    m_shader.setUniformValue(vertexColorLocation, QVector4D(0.0f, 1.0f, 0.0f, 1.0f));
//    if (keyPress) {
//        // Clear the buffer with the current clearing color
//        // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//        // Draw stuff
//        int matrixLocation = m_shader.uniformLocation("MVP");
//        getMVP();
//        m_shader.setUniformValue(matrixLocation, MVP);
//        int vertexColorLocation = m_shader.uniformLocation("ourColor");
//        m_shader.setUniformValue(vertexColorLocation, QVector4D(0.0f, 1.0f, 0.0f, 1.0f));
//    }
    glDrawArrays( GL_TRIANGLES, 0, 3 );

//    if (keyPress)
        update();

//    if (change) {
//        int msec = QTime::currentTime().msec();
//        float greenValue = (float)msec / 1000.0f;
//        int vertexColorLocation = m_shader.uniformLocation("ourColor");
//        m_shader.setUniformValue(vertexColorLocation, QVector4D(0.0f, greenValue, 0.0f, 1.0f));


//    }
}

void GLWidget::getMVP()
{
    float speed = 3.0f; // 3 units / second

    // 每帧延时
    float deltaTime = float(t.restart()) / 1000.0f;

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    QMatrix4x4 Projection;
    Projection.perspective(45.0f, (float)width()/(float)height(), 0.1f, 100.0f);

    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
//    QMatrix4x4 View;
//    View.lookAt(
//        QVector3D(4,3,3), // Camera is at (4,3,3), in World Space
//        QVector3D(0,0,0), // and looks at the origin
//        QVector3D(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//    );

    QVector3D right = QVector3D(1, 0, 0);
    QVector3D top = QVector3D(0, 1, 0);

//    if (keyPress && deltaTime > 0 && deltaTime < 0.035) {
//        if (keyPressText.compare("a") == 0) {
//            position += right * deltaTime * speed;
//            direction += right * deltaTime * speed;
//        }
//        if (keyPressText.compare("d") == 0) {
//            position -= right * deltaTime * speed;
//            direction -= right * deltaTime * speed;
//        }
//        if (keyPressText.compare("w") == 0) {
//            position -= top * deltaTime * speed;
//            direction -= top * deltaTime * speed;
//        }
//        if (keyPressText.compare("s") == 0) {
//            position += top * deltaTime * speed;
//            direction += top * deltaTime * speed;
//        }
//    }
    // 移动物体等同于反向移动镜头
    if (deltaTime > 0 && deltaTime < 0.035) {
        if (KEY_DOWN(0x41)) {
            position += right * deltaTime * speed;
            direction += right * deltaTime * speed;
        }
        if (KEY_DOWN(0x44)) {
            position -= right * deltaTime * speed;
            direction -= right * deltaTime * speed;
        }
        if (KEY_DOWN(0x57)) {
            position -= top * deltaTime * speed;
            direction -= top * deltaTime * speed;
        }
        if (KEY_DOWN(0x53)) {
            position += top * deltaTime * speed;
            direction += top * deltaTime * speed;
        }
    }
    if (change) {
        rotate += (deltaTime / T) * 360.0f;
    }

    // Camera matrix
    QMatrix4x4 View;
    View.lookAt(
        position,
        direction,
        QVector3D(-1,5,-2)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    QMatrix4x4 Model;
    // 通过rotate方法构造一个旋转矩阵，第一个参数定义旋转的角度，第二个参数定义旋转的轴（方向向量），如下为绕y轴旋转30度
    Model.rotate(rotate, QVector3D(0, 1, 0));
    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
}

void GLWidget::render()
{
    if (change) {
        change = false;
    } else {
        change = true;
    }
}

float GLWidget::getT()
{
    return T;
}

void GLWidget::setT(float t)
{
    T = t;
}


//void GLWidget::keyPressEvent(QKeyEvent *event)
//{
//    keyPress = true;
//    keyPressText = event->text();
//    update();
//}

//void GLWidget::keyReleaseEvent(QKeyEvent *event)
//{
//    keyPress = false;
//}
