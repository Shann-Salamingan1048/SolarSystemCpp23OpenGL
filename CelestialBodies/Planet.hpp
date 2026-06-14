#pragma once
#include <cstdint>

#include "CelestialBody.hpp"
#include "../Utilities/ResourceManager.hpp"
#include "../Utilities/DefaultValues.hpp"

enum class PlanetsEnum : uint8_t
{
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    PLUTO,

    END
};

inline void initPlanetTextures()
{
    // Diffuse
    ResourceManager::LoadTexture(MercuryDiffuse.name, MercuryDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(VenusDiffuse.name, VenusDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(EarthDiffuse.name, EarthDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);

    ResourceManager::LoadTexture(MarsDiffuse.name, MarsDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(JupiterDiffuse.name, JupiterDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(SaturnDiffuse.name, SaturnDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(UranusDiffuse.name, UranusDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(NeptuneDiffuse.name, NeptuneDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);

    // Specular
    //ResourceManager::LoadTexture(EarthSpecular.name, EarthSpecular.path, GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE, true);
}

inline void initPlanetShaders()
{
    ResourceManager::LoadShader("Planet", PlanetVertPath, PlanetFragPath);
}
class Planet : public CelestialBody
{
public:
    Planet(const PlanetsEnum& planet);

    void Draw() override;

};


struct PlanetData
{
    std::vector<std::unique_ptr<Planet>> bodies{};
    std::vector<uint32_t> indices{};
    std::vector<glm::vec3> positions{};
    std::vector<glm::vec3> scales{};
};