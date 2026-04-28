module;
#include <glad/glad.h>
#include <glm/glm.hpp>

export module Renderer;

import CelestialBody;
export struct Renderer
{

public:
    void DrawTexturedSphere(
        CelestialBody& celestial_body,
        const glm::mat4& model,
        const glm::mat4& view,
        const glm::mat4& projection
    ) const;
};