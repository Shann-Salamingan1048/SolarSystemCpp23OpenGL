module;
#include <glm/glm.hpp>

export module CelestialBody;
import Sphere;

class CelestialBody
{
public:
    explicit CelestialBody(float radius = 0.5f, uint32_t sectors = 36, uint32_t stacks = 18);
    CelestialBody(uint16_t width, uint16_t height, uint16_t depth,
           float radius = 0.5f, uint32_t sectors = 36, uint32_t stacks = 18);
    virtual ~CelestialBody() = default;

    CelestialBody(const CelestialBody&) = delete;
    CelestialBody operator=(const CelestialBody&) = delete;
    CelestialBody(CelestialBody&&) = delete;
    CelestialBody operator=(CelestialBody&&) = delete;

protected:
    Sphere shape;
};