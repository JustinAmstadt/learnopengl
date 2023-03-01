#version 330 core
layout (vertices = 4) out;

uniform float TessLevelInner = 3.0;
uniform float TessLevelOuter = 3.0;

void main() {
    gl_TessLevelInner[0] = TessLevelInner;
    gl_TessLevelOuter[0] = TessLevelOuter;
    gl_TessLevelOuter[1] = TessLevelOuter;
    gl_TessLevelOuter[2] = TessLevelOuter;
    gl_TessLevelOuter[3] = TessLevelOuter;
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
