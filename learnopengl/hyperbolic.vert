#version 410 core
/*
	Copyright 2021 Patrick Owen
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
 */

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 pos;
out vec4 normal;
out vec2 texCoord;
out vec4 pos_global;

void main()
{
	pos_global = view * model * vec4(vPos.x, vPos.y, vPos.z, 1.0);
	gl_Position = projection * pos_global;
	pos = vec4(vPos.x, vPos.y, vPos.z, 1.0);
	normal = vec4(vNormal, 1.0);
	texCoord = vTexCoord;
}