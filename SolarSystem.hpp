#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Engine/Engine.hpp"
#include "Renderer/Renderer.hpp"
#include "CelestialBodies/Planet.hpp"
#include "CelestialBodies/Star.hpp"

namespace Game
{
    struct PlanetData
    {
        std::vector<uint32_t> indices;
        std::vector<std::unique_ptr<Planet>> bodies;
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> scales;
    };

    struct StarData
    {
        std::vector<uint32_t> indices;
        std::vector<std::unique_ptr<Star>> bodies;
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> scales;
    };

    enum class MouseClickState : std::uint8_t
    {
        None,
        LeftClick,
        RightClick,
        Scroll,
    };

    class SolarSystem final : public Core::Engine
    {
    public:
        explicit SolarSystem(const char* title);
        SolarSystem(int width, int height, const char* title);

    public:
        void AddPlanet(
            uint32_t index,
            std::unique_ptr<Planet> planetBody,
            glm::vec3 pos,
            glm::vec3 scale
        );

        void AddStar(
            uint32_t index,
            std::unique_ptr<Star> starBody,
            glm::vec3 pos,
            glm::vec3 scale
        );

        void initPlanets();
        void initStars();

    protected:
        void processInput() override;
        void update() override;
        void render() override;
        void cleanUp() override;
        void initObjects() override;
        void initMath() override;
        void onKeyAction(int key, int action, int mods) override;
        void onMouseClick(int button, int action, int mods) override;

        void resizeObjects() const;

    private:
        Renderer m_renderer{};
        PlanetData planetData{};
        StarData starData{};

        MouseClickState m_mouseState{MouseClickState::None};
    };
}