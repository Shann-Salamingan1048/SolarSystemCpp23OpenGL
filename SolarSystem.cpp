#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "SolarSystem.hpp"
#include "Camera.hpp"
#include "Utilities/TimeUtils.hpp"
#include "Utilities/globalFunctions.hpp"
#include "Renderer/Renderer.hpp"
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
        AddCelestialBody<Planet>(
            0,
            std::make_unique<Planet>(PlanetsEnum::MERCURY),
            glm::vec3{-4.9f, 0.0f, -18.0f},
            glm::vec3{0.25f},
            3.0f,
            3.5f,
            planetsData
        );

        AddCelestialBody<Planet>(
            1,
            std::make_unique<Planet>(PlanetsEnum::VENUS),
            glm::vec3{-3.7f, 0.0f, -18.0f},
            glm::vec3{0.42f},
            4.5f,
            2.8f,
            planetsData
        );

        AddCelestialBody<Planet>(
            2,
            std::make_unique<Planet>(PlanetsEnum::EARTH),
            glm::vec3{-2.3f, 0.0f, -18.0f},
            glm::vec3{0.46f},
            6.0f,
            2.2f,
            planetsData
        );

        AddCelestialBody<Planet>(
            3,
            std::make_unique<Planet>(PlanetsEnum::MARS),
            glm::vec3{-0.9f, 0.0f, -18.0f},
            glm::vec3{0.34f},
            7.5f,
            1.8f,
            planetsData
        );

        AddCelestialBody<Planet>(
            4,
            std::make_unique<Planet>(PlanetsEnum::JUPITER),
            glm::vec3{1.2f, 0.0f, -18.0f},
            glm::vec3{1.05f},
            9.5f,
            1.2f,
            planetsData
        );

        AddCelestialBody<Planet>(
            5,
            std::make_unique<Planet>(PlanetsEnum::SATURN),
            glm::vec3{4.0f, 0.0f, -18.0f},
            glm::vec3{0.92f},
            12.0f,
            1.0f,
            planetsData
        );

        AddCelestialBody<Planet>(
            6,
            std::make_unique<Planet>(PlanetsEnum::URANUS),
            glm::vec3{6.4f, 0.0f, -18.0f},
            glm::vec3{0.75f},
            14.0f,
            0.7f,
            planetsData
        );

        AddCelestialBody<Planet>(
            7,
            std::make_unique<Planet>(PlanetsEnum::NEPTUNE),
            glm::vec3{8.4f, 0.0f, -18.0f},
            glm::vec3{0.70f},
            16.0f,
            0.5f,
            planetsData
        );
    }

    void SolarSystem::initStars()
    {
        AddCelestialBody<Star>(
            0,
            std::make_unique<Star>(StarsEnum::Sun),
            glm::vec3{-8.5f, 0.0f, -18.0f},
            glm::vec3{2.5f},
            0.0f,
            2.0f,
            starsData
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

        auto& cam = getCamera();
        cam.MovementSpeed = 10.0f;
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

        glClearColor(0.05f, 0.05f, 0.07f, 1.0f);
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
        for (uint32_t i = 0; i < starsData.bodies.size(); ++i)
        {
            sunPosition = starsData.positions[i];

            Renderer::DrawStar(
                *starsData.bodies[i],
                view,
                projection,
                starsData.scales[i],
                starsData.positions[i],
                cameraPosition,
                static_cast<float>(glfwGetTime())
            );
        }

        float time = static_cast<float>(glfwGetTime()) * 0.05f;

        for (size_t i = 0; i < planetsData.bodies.size(); i++)
        {
            glm::vec3 basePos = planetsData.positions[i];

            float radius = glm::length(glm::vec2(basePos.x, basePos.z));

            float orbitSpeed = planetsData.revolutionSpeeds[i];

            float angle = time * orbitSpeed;


            glm::vec3 finalPos;
            finalPos.x = sunPosition.x + cos(angle) * radius;
            finalPos.y = sunPosition.y;
            finalPos.z = sunPosition.z + sin(angle) * radius;


            float rotationSpeed = planetsData.rotationSpeeds[i];
            float rotationAngle = time * rotationSpeed;

            Renderer::DrawPlanet(
                *planetsData.bodies[i],
                view,
                projection,
                planetsData.scales[i],
                finalPos,
                sunPosition,
                cameraPosition,
                rotationAngle
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