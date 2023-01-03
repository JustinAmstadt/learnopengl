#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * material.ambient;
    
    vec3 unitNorm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    float diffuseFactor = max(dot(unitNorm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diffuseFactor * material.diffuse);

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, unitNorm);  

    float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (specFactor * material.specular);

    vec4 result = vec4(ambient + diffuse + specular, 1.0) * vertexColor;

    //texture(ourTexture, TexCoord)
    FragColor = result;
}