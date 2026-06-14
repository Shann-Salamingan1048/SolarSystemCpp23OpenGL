#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../CelestialBodies/CelestialBody.hpp"

class CelestialBody;

struct Renderer
{
    static void DrawPlanet(
        CelestialBody& body,
        const glm::mat4& view,
        const glm::mat4& projection,
        const glm::vec3& scale,
        const glm::vec3& position,
        const glm::vec3& sunPosition,
        const glm::vec3& cameraPosition,
        float rotationAngle
    );

    static void DrawStar(
        CelestialBody& body,
        const glm::mat4& view,
        const glm::mat4& projection,
        const glm::vec3& scale,
        const glm::vec3& position,
        const glm::vec3& cameraPosition,
        float time
    );
};