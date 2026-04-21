module;

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <print>

module SolarSystem;

import Camera;
import Time;
import globalFunctions;

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

    void SolarSystem::initObjects()
    {
        const auto& size = getScreenSize();
        const auto projection = glm::perspective(
            glm::radians(45.0f),
            static_cast<float>(size.x) / static_cast<float>(size.y),
            0.01f,
            100.0f);

        m_sphereShader.use();
        m_sphereShader.setMat4("projection", projection);
        m_sphereShader.setVec3("objectColor", glm::vec3{0.0f, 0.0f, 1.0f});
    }

    void SolarSystem::update()
    {
        using namespace ShannUtilities;
        Time::currentFrame = static_cast<float>(glfwGetTime());
        Time::deltaTime = Time::currentFrame - Time::lastFrame;
        Time::lastFrame = Time::currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto& view = getCamera().GetViewMatrix();
        m_sphereShader.use();
        m_sphereShader.setMat4("view", view);
    }

    void SolarSystem::render()
    {
        m_sphereShader.use();
        resizeObjects();

        for (const auto& spherePos : SpherePositions)
        {
            auto model = glm::mat4{1.0f};
            model = glm::translate(model, spherePos);

            m_sphereShader.setMat4("model", model);
            m_sphere.Draw();
        }
    }

    void SolarSystem::resizeObjects() const
    {
        const auto& size = getScreenSize();

        m_sphereShader.use();
        m_sphereShader.setVec3("aSize", glm::vec3{m_sphere.size.width, m_sphere.size.height, m_sphere.size.depth});
        m_sphereShader.setVec2("screenSize", glm::vec2{static_cast<float>(size.x), static_cast<float>(size.y)});
    }

    void SolarSystem::cleanUp()
    {
        m_sphereShader.deleteShader();
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

        if (button != GLFW_MOUSE_BUTTON_LEFT)
        {
            return;
        }

        if (action == GLFW_RELEASE)
        {
            m_mouseState = MouseClickState::None;
            return;
        }

        if (action != GLFW_PRESS || m_mouseState != MouseClickState::None)
        {
            return;
        }

        auto& camera = getCamera();
        const auto& size = getScreenSize();
        const auto mousePos = ShannUtilities::getMousePosition(&getWindow());
        const auto normalizedMousePos = ShannUtilities::getNormalizedVersion2D(mousePos, size);

        std::println("Mouse Pos: {}, {}", normalizedMousePos.x, normalizedMousePos.y);

        const auto rayClip = glm::vec4{normalizedMousePos.x, normalizedMousePos.y, -1.0f, 1.0f};
        const auto projection = glm::perspective(
            glm::radians(45.0f),
            static_cast<float>(size.x) / static_cast<float>(size.y),
            0.01f,
            100.0f);

        auto rayEye = glm::inverse(projection) * rayClip;
        rayEye = glm::vec4{rayEye.x, rayEye.y, -1.0f, 0.0f};

        const auto& view = camera.GetViewMatrix();
        auto rayWorld = glm::vec3{glm::inverse(view) * rayEye};
        rayWorld = glm::normalize(rayWorld);

        constexpr float spawnDistance = 5.0f;
        const glm::vec3 spawnPos = camera.Position + (rayWorld * spawnDistance);

        AddSphere(spawnPos);
        std::println("Spawned cube via Raycast at: {}, {}, {}", spawnPos.x, spawnPos.y, spawnPos.z);

        m_mouseState = MouseClickState::LeftClick;
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