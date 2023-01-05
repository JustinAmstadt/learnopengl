#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec4 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D emissionMap;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    
    vec3 unitNorm = normalize(Normal);

    vec3 lightDir;
    if(light.position.w == 1.0){
        lightDir = normalize(light.position.xyz - FragPos); //the light is a position vector
    }
    else{
        lightDir = normalize(-light.position.xyz); //the light is a direction vector
    }

    float diffuseFactor = max(dot(unitNorm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diffuseFactor * vec3(texture(material.diffuse, TexCoord));

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, unitNorm);  

    float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular = light.specular * specFactor * vec3(texture(material.specular, TexCoord));

    //vec3 emission = texture(emissionMap, TexCoord).rgb;

    //attenuation. values default set to -1.0, so in order to use it, the values must be reset
    if(light.constant > 0.0){
        float distance = length(vec3(light.position) - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  

        ambient  *= attenuation; 
        diffuse  *= attenuation;
        specular *= attenuation;   
    }

    FragColor = vec4(ambient + diffuse + specular, 1.0) * vertexColor;
}