#version 330

in vec3 ourColor;
out vec4 fragColor;

void main( void )
{
    fragColor = vec4(ourColor, 1.0f);
}
