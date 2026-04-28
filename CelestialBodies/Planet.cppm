module;

#include <cstdint>
export module Planet;
import CelestialBody;
import ResourceManager;


export enum class PlanetsEnum : uint8_t
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

export inline void initPlanetTextures();
export inline void initPlanetShaders();
export class Planet : public CelestialBody
{
public:
    Planet(const PlanetsEnum& planet);

    void Draw() override;



};