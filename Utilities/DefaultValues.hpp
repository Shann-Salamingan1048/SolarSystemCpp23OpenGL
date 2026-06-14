#pragma once

#include <cstdint>
#include <string>


constexpr inline float DEFAULT_RADIUS_SPHERE_VALUE = 0.5f;
constexpr inline uint8_t DEFAULT_STACKS_SPHERE_VALUE = 18;
constexpr inline uint8_t DEFAULT_SECTORS_SPHERE_VALUE = 36;

// Shaders
constexpr inline const char* PlanetVertPath = "glsl/planet.vert";
constexpr inline const char* PlanetFragPath = "glsl/planet.frag";
constexpr inline const char* StarVertPath = "glsl/star.vert";
constexpr inline const char* StarFragPath = "glsl/star.frag";

// Textures
struct TextureInfo
{
    std::string_view name;
    const char* path;
};
// Diffuse Texture
constexpr inline TextureInfo SunDiffuse
{
    .name = "SunDiffuse",
    .path = "Pics/SunDiffuse.jpg"
};
constexpr inline TextureInfo MercuryDiffuse
{
    .name = "MercuryDiffuse",
    .path = "Pics/MercuryDiffuse.jpg"
};
constexpr inline TextureInfo VenusDiffuse
{
    .name = "VenusDiffuse",
    .path = "Pics/VenusDiffuse.jpg"
};
constexpr inline TextureInfo EarthDiffuse
{
    .name = "EarthDiffuse",
    .path = "Pics/EarthDiffuse.jpg"
};

constexpr inline TextureInfo MarsDiffuse
{
    .name = "MarsDiffuse",
    .path = "Pics/MarsDiffuse.jpg"
};

constexpr inline TextureInfo JupiterDiffuse
{
    .name = "JupiterDiffuse",
    .path = "Pics/JupiterDiffuse.jpg"
};
constexpr inline TextureInfo SaturnDiffuse
{
    .name = "SaturnDiffuse",
    .path = "Pics/SaturnDiffuse.jpg"
};
constexpr inline TextureInfo UranusDiffuse
{
    .name = "UranusDiffuse",
    .path = "Pics/UranusDiffuse.jpg"
};
constexpr inline TextureInfo NeptuneDiffuse
{
    .name = "NeptuneDiffuse",
    .path = "Pics/NeptuneDiffuse.jpg"
};

// Specular Texture
constexpr inline TextureInfo EarthSpecular
{
    .name = "EarthSpecular",
    .path = "Pics/EarthSpecular.jpg"
};
