#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoords;

uniform vec3 customColor;
uniform sampler2D texture_diffuse;

void main()
{
    vec4 texColor = texture(texture_diffuse, TexCoords);
    FragColor = texColor;
}