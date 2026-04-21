module;

#include <cstdint>

export module SolarSystem;

import Engine;
import Sphere;
import Shader;
import Renderer;
export namespace Game
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
        void onKeyAction(int key, int action, int mods) override;
        void onMouseClick(int button, int action, int mods) override;

        void resizeObjects() const;

    private:

        Renderer m_renderer{};
        Shader m_sphereShader{SphereVertPath, SphereFragPath};
        MouseClickState m_mouseState{MouseClickState::None};
    };
}