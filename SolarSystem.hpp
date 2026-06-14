#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Engine/Engine.hpp"

#include "CelestialBodies/CelestialBody.hpp"
#include "CelestialBodies/Planet.hpp"
#include "CelestialBodies/Star.hpp"

#include <concepts>

namespace Game
{
    enum class MouseClickState : std::uint8_t
    {
        None,
        LeftClick,
        RightClick,
        Scroll,
    };

    template<typename T>
    concept CelestialBodyOnly = std::derived_from<T, CelestialBody>;

    class SolarSystem final : public Core::Engine
    {
    public:
        explicit SolarSystem(const char* title);
        SolarSystem(int width, int height, const char* title);

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
        template<CelestialBodyOnly T>
        struct CelestialBodyData
        {
            std::vector<uint32_t> indices;
            std::vector<std::unique_ptr<T>> bodies;

            std::vector<glm::vec3> positions;
            std::vector<glm::vec3> scales;

            std::vector<float> revolutionSpeeds;
            std::vector<float> rotationSpeeds;
        };

        using PlanetsData = CelestialBodyData<Planet>;
        using StarsData   = CelestialBodyData<Star>;


        template<CelestialBodyOnly T>
        void AddCelestialBody(
            uint32_t index,
            std::unique_ptr<T> body,
            glm::vec3 pos,
            glm::vec3 scale,
            float revSpeed,
            float rotSpeed,
            CelestialBodyData<T>& data
        )
        {
            data.indices.emplace_back(index);
            data.bodies.emplace_back(std::move(body));
            data.positions.emplace_back(pos);
            data.scales.emplace_back(scale);
            data.revolutionSpeeds.emplace_back(revSpeed);
            data.rotationSpeeds.emplace_back(rotSpeed);
        }

    private:
        void initPlanets();
        void initStars();

    private:
        PlanetsData planetsData{};
        StarsData starsData{};

        MouseClickState m_mouseState{MouseClickState::None};
    };
}