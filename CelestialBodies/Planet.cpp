#include "Planet.hpp"

Planet::Planet(const PlanetsEnum& planet)
{
    setShader(ResourceManager::GetShader("Planet"));

    initSphere(
        DEFAULT_RADIUS_SPHERE_VALUE,
        DEFAULT_SECTORS_SPHERE_VALUE,
        DEFAULT_STACKS_SPHERE_VALUE
    );

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