#version 330

in vec4 vertex;
in vec3 color;
uniform mat4 MVP;

out vec3 ourColor;

void main( void )
{
    gl_Position = MVP * vertex;
    ourColor = color;
}
