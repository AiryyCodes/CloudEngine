#pragma once

const char* MAIN_FRAG = R"(
#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};

struct DirLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 fragPos;

uniform Material material;

uniform DirLight dirLight;
#define NR_POINT_LIGHTS 128
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform int numPointLights;

uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, uv));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, uv));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, uv));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
				
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, uv));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, uv));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, uv));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // vec3 result = CalcDirLight(dirLight, norm, viewDir);
	// for(int i = 0; i < numPointLights; i++)
    	// result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);    

	vec3 result = vec3(0.5f, 0.3f, 0.1f);

	vec4 texColor = texture(material.diffuse, uv);
	//if (texColor.a < 0.1)
		//discard;

    FragColor = vec4(result, 1.0);
}
)";
