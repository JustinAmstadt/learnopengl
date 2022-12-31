#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 unitNorm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diffuseFactor = max(dot(unitNorm, lightDir), 0.0);
    vec3 diffuse = diffuseFactor * lightColor;

    vec4 result = vec4(ambient + diffuse, 1.0) * vertexColor;

    FragColor = result;
    //FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0);
}