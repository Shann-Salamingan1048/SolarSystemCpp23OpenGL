#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "SolarSystem.hpp"
#include "Camera.hpp"
#include "Utilities/TimeUtils.hpp"
#include "Utilities/globalFunctions.hpp"

namespace Game
{
    SolarSystem::SolarSystem(const char* title)
        : Core::Engine(title)
    {
    }

    SolarSystem::SolarSystem(int width, int height, const char* title)
        : Core::Engine(width, height, title)
    {
    }

    void SolarSystem::initPlanets()
    {
        AddPlanet(
            0,
            std::make_unique<Planet>(PlanetsEnum::MERCURY),
            glm::vec3{-4.9f, 0.0f, -18.0f},
            glm::vec3{0.25f}
        );

        AddPlanet(
            1,
            std::make_unique<Planet>(PlanetsEnum::VENUS),
            glm::vec3{-3.7f, 0.0f, -18.0f},
            glm::vec3{0.42f}
        );

        AddPlanet(
            2,
            std::make_unique<Planet>(PlanetsEnum::EARTH),
            glm::vec3{-2.3f, 0.0f, -18.0f},
            glm::vec3{0.46f}
        );

        AddPlanet(
            3,
            std::make_unique<Planet>(PlanetsEnum::MARS),
            glm::vec3{-0.9f, 0.0f, -18.0f},
            glm::vec3{0.34f}
        );

        AddPlanet(
            4,
            std::make_unique<Planet>(PlanetsEnum::JUPITER),
            glm::vec3{1.2f, 0.0f, -18.0f},
            glm::vec3{1.05f}
        );

        AddPlanet(
            5,
            std::make_unique<Planet>(PlanetsEnum::SATURN),
            glm::vec3{4.0f, 0.0f, -18.0f},
            glm::vec3{0.92f}
        );

        AddPlanet(
            6,
            std::make_unique<Planet>(PlanetsEnum::URANUS),
            glm::vec3{6.4f, 0.0f, -18.0f},
            glm::vec3{0.68f}
        );

        AddPlanet(
            7,
            std::make_unique<Planet>(PlanetsEnum::NEPTUNE),
            glm::vec3{8.4f, 0.0f, -18.0f},
            glm::vec3{0.66f}
        );
    }

    void SolarSystem::initStars()
    {
        AddStar(
            0,
            std::make_unique<Star>(StarsEnum::Sun),
            glm::vec3{-8.5f, 0.0f, -18.0f},
            glm::vec3{2.5f}
        );
    }

    void SolarSystem::initObjects()
    {
        initPlanetShaders();
        initStarShaders();

        initPlanetTextures();
        initStarTextures();

        initStars();
        initPlanets();
    }

    void SolarSystem::AddPlanet(
        uint32_t index,
        std::unique_ptr<Planet> planetBody,
        glm::vec3 pos,
        glm::vec3 scale
    )
    {
        planetData.indices.emplace_back(index);
        planetData.bodies.emplace_back(std::move(planetBody));
        planetData.positions.emplace_back(pos);
        planetData.scales.emplace_back(scale);
    }

    void SolarSystem::AddStar(
        uint32_t index,
        std::unique_ptr<Star> starBody,
        glm::vec3 pos,
        glm::vec3 scale
    )
    {
        starData.indices.emplace_back(index);
        starData.bodies.emplace_back(std::move(starBody));
        starData.positions.emplace_back(pos);
        starData.scales.emplace_back(scale);
    }

    void SolarSystem::initMath()
    {
    }

    void SolarSystem::update()
    {
        using namespace ShannUtilities;

        Time::currentFrame = static_cast<float>(glfwGetTime());
        Time::deltaTime = Time::currentFrame - Time::lastFrame;
        Time::lastFrame = Time::currentFrame;

        glEnable(GL_DEPTH_TEST);

        glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SolarSystem::render()
    {
        resizeObjects();

        const auto& size = getScreenSize();

        const auto projection = glm::perspective(
            glm::radians(45.0f),
            static_cast<float>(size.x) / static_cast<float>(size.y),
            0.01f,
            100.0f
        );

        const glm::mat4 view = getCamera().GetViewMatrix();
        const glm::vec3 cameraPosition = getCamera().Position;

        glm::vec3 sunPosition{-8.5f, 0.0f, -18.0f};

        // Draw sun
        for (uint32_t i = 0; i < starData.bodies.size(); ++i)
        {
            sunPosition = starData.positions[i];

            m_renderer.DrawStar(
                *starData.bodies[i],
                view,
                projection,
                starData.scales[i],
                starData.positions[i],
                cameraPosition,
                static_cast<float>(glfwGetTime())
            );
        }

        // Draw planets using the sun as light source
        for (uint32_t i = 0; i < planetData.bodies.size(); ++i)
        {
            m_renderer.DrawPlanet(
                *planetData.bodies[i],
                view,
                projection,
                planetData.scales[i],
                planetData.positions[i],
                sunPosition,
                cameraPosition
            );
        }
    }

    void SolarSystem::resizeObjects() const
    {
    }

    void SolarSystem::cleanUp()
    {
    }

    void SolarSystem::onKeyAction(int key, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            requestClose();
        }
    }

    void SolarSystem::onMouseClick(int button, int action, int mods)
    {
    }

    void SolarSystem::processInput()
    {
        auto& camera = getCamera();
        auto& window = getWindow();

        using namespace ShannUtilities;

        if (glfwGetKey(&window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(CameraUtils::Camera_Movement::FORWARD, Time::deltaTime);
        }

        if (glfwGetKey(&window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(CameraUtils::Camera_Movement::BACKWARD, Time::deltaTime);
        }

        if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(CameraUtils::Camera_Movement::LEFT, Time::deltaTime);
        }

        if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(CameraUtils::Camera_Movement::RIGHT, Time::deltaTime);
        }
    }
}