module;
#include <glad/glad.h>

module Renderer;

void Renderer::DrawSphere(
    Shader& shader,
    Sphere& sphere,
    const glm::mat4& model,
    const glm::mat4& view,
    const glm::mat4& projection
) const
{
    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    sphere.Draw();
}

void Renderer::DrawTexturedSphere(
    Shader& shader,
    Sphere& sphere,
    GLuint texture,
    const glm::mat4& model,
    const glm::mat4& view,
    const glm::mat4& projection
) const
{
    shader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    shader.setInt("texture1", 0);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    sphere.Draw();
}