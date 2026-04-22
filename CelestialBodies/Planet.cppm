module;


export module Planet;
import CelestialBody;
import ResourceManager;


export enum class PlanetsEnum
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

export class Planet : public CelestialBody
{
public:
    Planet(PlanetsEnum planet);

    void Draw() override;



};