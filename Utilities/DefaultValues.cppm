module;
#include <cstdint>
#include <string>
export module DefaultValues;

export constexpr inline float DEFAULT_RADIUS_SPHERE_VALUE = 0.5f;
export constexpr inline uint8_t DEFAULT_SECTORS_SPHERE_VALUE = 36;
export constexpr inline uint8_t DEFAULT_STACKS_SPHERE_VALUE = 18;

// Shaders
export constexpr inline const char* SphereVertPath = "glsl/sphere.vert";
export constexpr inline const char* SphereFragPath = "glsl/sphere.frag";


// Textures
export struct TextureInfo
{
    std::string_view name;
    const char* path;
};
// Diffuse Texture
export constexpr inline TextureInfo SunDiffuse
{
    .name = "SunDiffuse",
    .path = "Pics/SunDiffuse.jpg"
};
export constexpr inline TextureInfo MercuryDiffuse
{
    .name = "MercuryDiffuse",
    .path = "Pics/MercuryDiffuse.jpg"
};
export constexpr inline TextureInfo VenusDiffuse
{
    .name = "VenusDiffuse",
    .path = "Pics/VenusDiffuse.jpg"
};
export constexpr inline TextureInfo EarthDiffuse
{
    .name = "EarthDiffuse",
    .path = "Pics/EarthDiffuse.jpg"
};

export constexpr inline TextureInfo MarsDiffuse
{
    .name = "MarsDiffuse",
    .path = "Pics/MarsDiffuse.jpg"
};

export constexpr inline TextureInfo JupiterDiffuse
{
    .name = "JupiterDiffuse",
    .path = "Pics/JupiterDiffuse.jpg"
};
export constexpr inline TextureInfo SaturnDiffuse
{
    .name = "SaturnDiffuse",
    .path = "Pics/SaturnDiffuse.jpg"
};
export constexpr inline TextureInfo UranusDiffuse
{
    .name = "UranusDiffuse",
    .path = "Pics/UranusDiffuse.jpg"
};
export constexpr inline TextureInfo NeptuneDiffuse
{
    .name = "NeptuneDiffuse",
    .path = "Pics/NeptuneDiffuse.jpg"
};

// Specular Texture
export constexpr inline TextureInfo EarthSpecular
{
    .name = "EarthSpecular",
    .path = "Pics/EarthSpecular.jpg"
};