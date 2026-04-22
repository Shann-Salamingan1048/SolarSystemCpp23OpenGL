module;
#include <vector>
#include <cstdint>
#include <glad/glad.h>
#include <glm/glm.hpp>

export module Sphere;

import BaseShape3D;
import VAO;
import VBO;
import EBO;


export class Sphere : public BaseShape3D
{
public:
    Sphere() = default;
    explicit Sphere(float radius, uint32_t sectors, uint32_t stacks);
    Sphere(uint16_t width, uint16_t height, uint16_t depth,
           float radius = 0.5f, uint32_t sectors = 36, uint32_t stacks = 18);
    ~Sphere() override;

    void Draw() override;

    void init(float radius = 0.5f, uint32_t sectors = 36, uint32_t stacks = 18);
    void init(uint16_t width, uint16_t height, uint16_t depth,
              float radius = 0.5f, uint32_t sectors = 36, uint32_t stacks = 18);

private:
    void BuildSphere(float radius, uint32_t sectors, uint32_t stacks);
    void SetupBuffers();
    void ReleaseBuffers();

private:
    std::vector<GLfloat> m_vertices;
    std::vector<GLuint>  m_indices;
    GLsizei m_indexCount = 0;

    VAO m_vao{};
    VBO m_vbo{};
    EBO m_ebo{};
};

export inline std::vector<glm::vec3> SpherePositions{};

export inline void AddSphere(glm::vec3 spawnSphere)
{
    SpherePositions.emplace_back(spawnSphere);
}