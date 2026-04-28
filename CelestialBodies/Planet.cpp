module;
#include "glad/glad.h"
module Planet;
import DefaultValues;
import Shader;
import Texture;
void initPlanetTextures()
{
    // Diffuse
    ResourceManager::LoadTexture(SunDiffuse.name, SunDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(MercuryDiffuse.name, MercuryDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(VenusDiffuse.name, VenusDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(EarthDiffuse.name, EarthDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);

    ResourceManager::LoadTexture(MarsDiffuse.name, MarsDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(JupiterDiffuse.name, JupiterDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(SaturnDiffuse.name, SaturnDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(UranusDiffuse.name, UranusDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(NeptuneDiffuse.name, NeptuneDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);

    // Specular
    ResourceManager::LoadTexture(EarthSpecular.name, EarthDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE, true);
}
void initPlanetShaders()
{
    ResourceManager::LoadShader("Planet",SphereVertPath,SphereFragPath);
}
Planet::Planet(const PlanetsEnum &planet)
{
    initPlanetTextures();
    initPlanetShaders();

    setShader(ResourceManager::GetShader("Planet"));
    initSphere(DEFAULT_RADIUS_SPHERE_VALUE, DEFAULT_SECTORS_SPHERE_VALUE,DEFAULT_STACKS_SPHERE_VALUE);

    switch (planet)
    {
        case PlanetsEnum::MERCURY:
            setTexture(ResourceManager::GetTexture(MercuryDiffuse.name));
            break;
        case PlanetsEnum::VENUS:
            setTexture(ResourceManager::GetTexture(VenusDiffuse.name));
            break;
        case PlanetsEnum::EARTH:
            setTexture(ResourceManager::GetTexture(EarthDiffuse.name));
            break;
        case PlanetsEnum::MARS:
            setTexture(ResourceManager::GetTexture(MarsDiffuse.name));
            break;
        case PlanetsEnum::JUPITER:
            setTexture(ResourceManager::GetTexture(JupiterDiffuse.name));
            break;
        case PlanetsEnum::SATURN:
            setTexture(ResourceManager::GetTexture(SaturnDiffuse.name));
            break;
        case PlanetsEnum::URANUS:
            setTexture(ResourceManager::GetTexture(UranusDiffuse.name));
            break;
        case PlanetsEnum::NEPTUNE:
            setTexture(ResourceManager::GetTexture(NeptuneDiffuse.name));
            break;

        default:
            setTexture(ResourceManager::GetTexture(MercuryDiffuse.name));
            break;

    }
}

void Planet::Draw()
{
    p_sphere.Draw();
}
