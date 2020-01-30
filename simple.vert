#version 330

in vec3 vertex;
in vec3 color;
in vec2 texCoord;
uniform mat4 MVP;

out vec3 ourColor;
out vec2 TexCoord;

void main( void )
{
    gl_Position = MVP * vec4(vertex, 1.0f);
    ourColor = color;
    TexCoord = texCoord;
}
