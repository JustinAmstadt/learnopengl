#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 4) in float aDistFromStart;

out vec4 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float wingAngle; // must be in radians

void main()
{
  Color = aColor;
  float yPos = aPos.y;
  float xPos = aPos.x;

  yPos = aDistFromStart * sin(wingAngle);
  xPos = aDistFromStart * cos(wingAngle);

	gl_Position = projection * view * model * vec4(xPos, yPos, aPos.z, 1.0);
}
