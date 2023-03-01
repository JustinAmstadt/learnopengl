#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec2 TexCoord;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define SCALE 10.0
uniform float time;

float calculateSurface(float x, float z) {
    float y = 0.0;
    y += (sin(x * 1.0 / SCALE + time * 1.0) + sin(x * 2.3 / SCALE + time * 1.5) + sin(x * 3.3 / SCALE + time * 0.4)) / 3.0;
    y += (sin(z * 0.2 / SCALE + time * 1.8) + sin(z * 1.8 / SCALE + time * 1.8) + sin(z * 2.8 / SCALE + time * 0.8)) / 3.0;
    return y;
}

void main() 
{
    TexCoord = aTexCoord;

    vec3 pos = aPos;
    float strength = 1.0;
    pos.y += strength * calculateSurface(pos.x, pos.z);
    pos.y -= strength * calculateSurface(0.0, 0.0);

    FragPos = vec3(view * model * vec4(pos, 1.0));

    gl_Position = projection * view * model * vec4(pos, 1.0);
}  
