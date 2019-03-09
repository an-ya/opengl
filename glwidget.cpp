#include <QCoreApplication>
#include <QSurfaceFormat>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QVector3D>
#include "glwidget.h"

GLWidget::GLWidget( QWidget* parent )
 : QOpenGLWidget( parent )
{
    QSurfaceFormat format;
    format.setSamples(16);

    setFormat(format);
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Set the clear color to black
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    int matrixLocation;
    // Prepare a complete shader program…
    if ( prepareShaderProgram( ":/new/simple.vert", ":/new/simple.frag" ) ) {
        matrixLocation = m_shader.uniformLocation("MVP");
    } else {
        return;
    }

    // We need us some vertex data. Start simple with a triangle ;-)
    float points[] = {
        -0.5f,-0.5f,0.0f,1.0f,
        0.5f,-0.5f,0.0f,1.0f,
        0.0f,0.5f,0.0f,1.0f
    };

    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QGLBuffer::StaticDraw );
    if ( !m_vertexBuffer.bind() )
    {
        qWarning() << "Could not bind vertex buffer to the context";
        return;
    }
    m_vertexBuffer.allocate( points, 3 * 4 * sizeof( float ) );

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    QMatrix4x4 Projection;
    Projection.perspective(45.0f, 1, 0.1f, 100.0f);

    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    QMatrix4x4 View;
    View.lookAt(
        QVector3D(4,3,3), // Camera is at (4,3,3), in World Space
        QVector3D(0,0,0), // and looks at the origin
        QVector3D(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    QMatrix4x4 Model;
    // Our ModelViewProjection : multiplication of our 3 matrices
    QMatrix4x4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if ( !m_shader.bind() )
    {
        qWarning() << "Could not bind shader program to context";
        return;
    }

    // Enable the "vertex" attribute to bind it to our currently bound
    // vertex buffer.
    m_shader.setAttributeBuffer( "vertex", GL_FLOAT, 0, 4 );
    m_shader.enableAttributeArray( "vertex" );
    m_shader.setUniformValue(matrixLocation, MVP);
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
    // Clear the buffer with the current clearing color
    // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw stuff
    glDrawArrays( GL_TRIANGLES, 0, 3 );
}
