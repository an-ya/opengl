#version 330

out vec4 fragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main( void )
{
    fragColor = vec4(ourColor, 1.0) + texture(ourTexture, TexCoord);
    //    fragColor = vec4(ourColor, 1.0);
}
