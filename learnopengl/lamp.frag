#version 410 core
out vec4 FragColor;

in vec4 Color;

uniform vec3 lightColor;

void main()
{
    FragColor = Color;
}