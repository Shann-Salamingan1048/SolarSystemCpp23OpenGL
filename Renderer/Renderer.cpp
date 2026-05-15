#include "Renderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shader.hpp"
#include "../Texture.hpp"

void Renderer::DrawTexturedSphere(
    CelestialBody& body,
    const glm::mat4& view,
    const glm::mat4& projection,
    const glm::vec3& scale,
    const glm::vec3& position
)
{
    auto& shader = body.getShader();
    const auto& texture = body.getTexture();

    shader.use();

    glm::mat4 model{1.0f};
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    shader.setInt("diffuseTexture", 0);

    body.Draw();
}