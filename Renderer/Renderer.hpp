#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "../CelestialBodies/CelestialBody.hpp"

class CelestialBody;

struct Renderer
{

public:
    void DrawTexturedSphere(
            CelestialBody& body,
            const glm::mat4& view,
            const glm::mat4& projection,
            const glm::vec3& scale,
            const glm::vec3& position
    );
};