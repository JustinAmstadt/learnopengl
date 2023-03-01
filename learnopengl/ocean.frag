#version 330 core

struct FogInfo{
	float maxDist;
	float minDist;
	vec3 color;
};

in vec2 TexCoord;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D text;

void main()
{
	FogInfo f;
	f.maxDist = 50.0;
	f.minDist = 2.0;
	f.color = vec3(0.4, 0.4, 0.4);

	float dist = abs(FragPos.z);
	float fogFactor = (f.maxDist - dist) / (f.maxDist - f.minDist);
	fogFactor = clamp(fogFactor, 0.0, 1.0);

	vec4 outputColor;

	if(texture(text, TexCoord) != vec4(0.0)){
		outputColor = mix(vec4(f.color, 1.0), texture(text, TexCoord), fogFactor);
	}
	else{
		outputColor = vec4(0.8, 0.8, 0.8, 1.0);
	}

	FragColor = outputColor;
}
