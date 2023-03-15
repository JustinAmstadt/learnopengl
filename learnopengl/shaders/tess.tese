#version 330 core
layout (triangles, equal_spacing, cw) in;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 P0 = gl_in[0].gl_Position;
    vec4 P1 = gl_in[1].gl_Position;
    vec4 P2 = gl_in[2].gl_Position;
    vec4 P3 = gl_in[3].gl_Position;
    vec4 pos = mix(mix(P0, P1, gl_TessCoord.x), mix(P3, P2, gl_TessCoord.x), gl_TessCoord.y);

    gl_Position = projection * view * model * pos;
}
