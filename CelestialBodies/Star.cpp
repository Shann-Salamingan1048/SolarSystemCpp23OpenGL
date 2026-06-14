#include "Star.hpp"

Star::Star(const StarsEnum& star)
{
    setShader(ResourceManager::GetShader("Star"));

    initSphere(
        DEFAULT_RADIUS_SPHERE_VALUE,
        DEFAULT_SECTORS_SPHERE_VALUE,
        DEFAULT_STACKS_SPHERE_VALUE
    );

    switch (star)
    {
        case StarsEnum::Sun:
            setTexture(ResourceManager::GetTexture(SunDiffuse.name));
            break;

        default:
            setTexture(ResourceManager::GetTexture(SunDiffuse.name));
            break;
    }
}

void Star::Draw()
{
    p_sphere.Draw();
}