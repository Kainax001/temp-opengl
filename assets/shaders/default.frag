#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D texture_diffuse;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    float ambient = 0.20f;

    vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

    vec4 texColor = texture(texture_diffuse, TexCoords);
    
    FragColor = texColor * lightColor * (ambient + diffuse + specular);
}