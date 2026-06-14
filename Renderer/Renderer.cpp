#include "Renderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shader.hpp"
#include "../Texture.hpp"

void Renderer::DrawPlanet(
    CelestialBody& body,
    const glm::mat4& view,
    const glm::mat4& projection,
    const glm::vec3& scale,
    const glm::vec3& position,
    const glm::vec3& sunPosition,
    const glm::vec3& cameraPosition,
    float rotationAngle
)
{
    auto& shader = body.getShader();
    const auto& texture = body.getTexture();

    shader.use();

    glm::mat4 model{1.0f};
    model = glm::translate(glm::mat4(1.0f), position);
    model = glm::rotate(model, rotationAngle, glm::vec3(0,1,0));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    shader.setVec3("viewPos", cameraPosition);

    shader.setVec3("sunPosition", sunPosition);
    shader.setVec3("sunColor", glm::vec3{1.0f, 0.82f, 0.55f});

    shader.setFloat("sunIntensity", 75.0f * 5.0f);
    shader.setFloat("ambientStrength", 0.05f);
    shader.setFloat("shininess", 32.0f);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    shader.setInt("diffuseTexture", 0);

    body.Draw();
}

void Renderer::DrawStar(
    CelestialBody& body,
    const glm::mat4& view,
    const glm::mat4& projection,
    const glm::vec3& scale,
    const glm::vec3& position,
    const glm::vec3& cameraPosition,
    float time
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

    shader.setVec3("viewPos", cameraPosition);
    shader.setVec3("sunColor", glm::vec3{1.0f, 0.55f, 0.18f});
    shader.setFloat("emissionStrength", 1.8f);
    shader.setFloat("time", time);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    shader.setInt("diffuseTexture", 0);

    body.Draw();
}