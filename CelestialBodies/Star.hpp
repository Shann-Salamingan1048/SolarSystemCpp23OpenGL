#pragma once
#include <cstdint>

#include "CelestialBody.hpp"
#include "../Utilities/ResourceManager.hpp"
#include "../Utilities/DefaultValues.hpp"

enum class StarsEnum : uint8_t
{
    Sun,
    END
};

inline void initStarTextures()
{
    // Diffuse
    ResourceManager::LoadTexture(SunDiffuse.name, SunDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
}

inline void initStarShaders()
{
    ResourceManager::LoadShader("Star", StarVertPath, StarFragPath);
}
class Star : public CelestialBody
{
public:
    Star(const StarsEnum& star);

    void Draw() override;

};


struct StarData
{
    std::vector<std::unique_ptr<Star>> bodies{};
    std::vector<uint32_t> indices{};
    std::vector<glm::vec3> positions{};
    std::vector<glm::vec3> scales{};
};