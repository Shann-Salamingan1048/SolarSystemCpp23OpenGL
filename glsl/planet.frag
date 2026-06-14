#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D diffuseTexture;

uniform vec3 viewPos;

uniform vec3 sunPosition;
uniform vec3 sunColor;

uniform float sunIntensity;
uniform float ambientStrength;
uniform float shininess;

void main()
{
    vec3 textureColor = texture(diffuseTexture, TexCoords).rgb;

    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Direction from this planet fragment to the sun
    vec3 lightDir = normalize(sunPosition - FragPos);

    // 1.0 when facing the sun, 0.0 when facing away
    float sunlightFacing = max(dot(normal, lightDir), 0.0);

    // Distance-based light falloff
    float distanceToSun = length(sunPosition - FragPos);

    float attenuation = sunIntensity / (distanceToSun * distanceToSun);
    attenuation = clamp(attenuation, 0.0, 2.5);

    vec3 ambient = textureColor * ambientStrength;

    vec3 diffuse = textureColor * sunColor * sunlightFacing * attenuation;

    vec3 reflectDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = sunColor * specAmount * attenuation * 0.25;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}