module;
#include <glad/glad.h>

module Renderer;



void Renderer::DrawTexturedSphere(
    CelestialBody& celestial_body,
    const glm::mat4& model,
    const glm::mat4& view,
    const glm::mat4& projection
) const
{
    celestial_body.getShader().use();
}