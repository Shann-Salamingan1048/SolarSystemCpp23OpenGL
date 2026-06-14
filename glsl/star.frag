#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D diffuseTexture;

uniform vec3 viewPos;
uniform vec3 sunColor;
uniform float emissionStrength;
uniform float time;

void main()
{
    vec3 textureColor = texture(diffuseTexture, TexCoords).rgb;

    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    float rim = 1.0 - max(dot(normal, viewDir), 0.0);
    rim = pow(rim, 1.6);

    float pulse = 0.96 + 0.04 * sin(time * 2.0);

    // Use more of the actual sun texture
    vec3 textureBasedColor = textureColor;

    // Add only a soft warm tint, not too much yellow/orange
    vec3 softWarmTint = vec3(1.0, 0.62, 0.25);

    vec3 sunSurface = mix(textureBasedColor, softWarmTint, 0.22);

    // Brighten without washing out the texture
    vec3 emissive = sunSurface * emissionStrength * pulse;

    // Subtle edge brightness
    emissive += sunColor * rim * 0.35;

    // Prevent pure white overexposure
    emissive = emissive / (emissive + vec3(1.0));

    // Small final boost
    emissive *= 1.25;

    FragColor = vec4(emissive, 1.0);
}