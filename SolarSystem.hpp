
#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "Engine/Engine.hpp"
#include "CelestialBodies/CelestialBody.hpp"
#include "Renderer/Renderer.hpp"


namespace Game
{
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

    private:
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

        using CelestialBodyPtr = std::unique_ptr<CelestialBody, std::default_delete<CelestialBody>>;

        std::vector<CelestialBodyPtr> m_celestialBodies;

        MouseClickState m_mouseState{MouseClickState::None};
    };
}