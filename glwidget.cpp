#include <QApplication>
#include <QCoreApplication>
#include <QSurfaceFormat>
#include <QKeyEvent>
#include <QVector3D>
#include <QVector4D>
#include <QDateTime>
#include <QOpenGLContext>
#include <QOpenGLTexture>
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
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Prepare a complete shader program…
    if ( !prepareShaderProgram( ":/new/simple.vert", ":/new/simple.frag" ) )
        return;

    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if ( !m_shader.bind() )
    {
        qWarning() << "Could not bind shader program to context";
        return;
    }

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };

    static const GLfloat g_texture_buffer_data[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         50.0f,  -2.0f, 50.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // 右上
         50.0f, -2.0f, -50.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 右下
        -50.0f, -2.0f, -50.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // 左下
        -50.0f,  -2.0f, 50.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f    // 左上
    };

    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QGLBuffer::StaticDraw );
    if ( m_vertexBuffer.bind() ) {
        m_vertexBuffer.allocate(g_vertex_buffer_data, sizeof(g_vertex_buffer_data) );
        m_shader.enableAttributeArray( 0 );
    } else {
        qWarning() << "Could not bind vertex buffer to the context";
        return;
    }

    m_colorBuffer.create();
    m_colorBuffer.setUsagePattern( QGLBuffer::StaticDraw );
    if ( m_colorBuffer.bind() ) {
        m_colorBuffer.allocate(g_color_buffer_data, sizeof(g_color_buffer_data) );
        m_shader.enableAttributeArray( 1 );
    } else {
        qWarning() << "Could not bind color buffer to the context";
        return;
    }

    m_textureBuffer.create();
    m_textureBuffer.setUsagePattern( QGLBuffer::StaticDraw );
    if ( m_textureBuffer.bind() ) {
        m_textureBuffer.allocate(g_texture_buffer_data, sizeof(g_texture_buffer_data) );
        m_shader.enableAttributeArray( 2 );
    } else {
        qWarning() << "Could not texture color buffer to the context";
        return;
    }

    myTexture = new QOpenGLTexture(QImage(QString(":/new/side1.png")).mirrored());
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

    getMVP(false);
    m_shader.setUniformValue("MVP", MVP);

    m_vertexBuffer.bind();
    m_shader.setAttributeBuffer( 0, GL_FLOAT, 0 * sizeof( float ), 3, 3 * sizeof( float ));
    m_colorBuffer.bind();
    m_shader.setAttributeBuffer( 1, GL_FLOAT, 0 * sizeof( float ), 3, 3 * sizeof( float ));
    glDrawArrays( GL_TRIANGLES, 0, 36 );
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    getMVP(true);
    m_shader.setUniformValue("MVP", MVP);

    m_textureBuffer.bind();
    m_shader.setAttributeBuffer( 0, GL_FLOAT, 0 * sizeof( float ), 3, 8 * sizeof( float ));
    m_shader.setAttributeBuffer( 1, GL_FLOAT, 3 * sizeof( float ), 3, 8 * sizeof( float ));
    m_shader.setAttributeBuffer( 2, GL_FLOAT, 6 * sizeof( float ), 2, 8 * sizeof( float ));
    myTexture->bind();
    glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
    myTexture->release();

    update();
}

void GLWidget::getMVP(bool isStatic)
{
    float speed = 3.0f; // 3 units / second

    deltaTime = float(t.restart()) / 1000.0f;

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    QMatrix4x4 Projection;
    Projection.perspective(camera->getZoom(deltaTime), (float)width()/(float)height(), 0.1f, 500.0f);

    // Camera matrix
    if (deltaTime > 0 && deltaTime < 0.035) {
        if (KEY_DOWN(0x25)) {
            camera->ProcessKeyboard(3, deltaTime);
        }
        if (KEY_DOWN(0x26)) {
            camera->ProcessKeyboard(1, deltaTime);
        }
        if (KEY_DOWN(0x27)) {
            camera->ProcessKeyboard(4, deltaTime);
        }
        if (KEY_DOWN(0x28)) {
            camera->ProcessKeyboard(2, deltaTime);
        }
    }
    QMatrix4x4 View = camera->GetViewMatrix();

    // Model matrix : an identity matrix (model will be at the origin)
    QMatrix4x4 Model;

    QVector3D right = QVector3D(1, 0, 0);
    QVector3D top = QVector3D(0, 1, 0);
    if (deltaTime > 0 && deltaTime < 0.035) {
        if (KEY_DOWN(0x41)) {
            object_position -= right * deltaTime * speed;
        }
        if (KEY_DOWN(0x44)) {
            object_position += right * deltaTime * speed;
        }
        if (KEY_DOWN(0x57)) {
            object_position += top * deltaTime * speed;
        }
        if (KEY_DOWN(0x53)) {
            object_position -= top * deltaTime * speed;
        }
    }
    Model.translate(object_position);

    if (change) {
        rotate += (deltaTime / T) * 360.0f;
    }
    if (!isStatic) {
       Model.rotate(rotate, 0.0f, 1.0f, 0.0f);
    }

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

void GLWidget::setKeyPressText(QString s)
{
    keyPressText = s;
//    update();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = lastPos.y() - event->y();

    if (event->buttons() & Qt::LeftButton) {
        camera->ProcessMouseMovement(dx, dy, 0.0f);
    } else if (event->buttons() & Qt::RightButton) {
        camera->ProcessMouseMovement(0.0f, 0.0f, dx);
    }
    lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
//    emit clicked();
}

void GLWidget::wheelEvent(QWheelEvent *event)    // 滚轮事件
{
    camera->ProcessMouseScroll(event->delta());
}


//void GLWidget::keyPressEvent(QKeyEvent *ev)
//{

//}

//void GLWidget::keyReleaseEvent(QKeyEvent *ev)
//{

//}
