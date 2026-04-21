module;
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

export module Sphere;

import BaseShape3D;
import VAO;
import VBO;
import EBO;

export constexpr const char* SphereVertPath = "glsl/sphere.vert";
export constexpr const char* SphereFragPath = "glsl/sphere.frag";

export class Sphere : public BaseShape3D
{
public:
    explicit Sphere(float radius = 0.5f, uint32_t sectors = 36, uint32_t stacks = 18);
    Sphere(uint16_t width, uint16_t height, uint16_t depth,
           float radius = 0.5f, uint32_t sectors = 36, uint32_t stacks = 18);
    ~Sphere() override;

    void Draw() override;

private:
    void BuildSphere(float radius, uint32_t sectors, uint32_t stacks);

private:
    std::vector<GLfloat>  m_vertices; // x, y, z
    std::vector<GLuint>   m_indices;
    GLsizei               m_indexCount = 0;

    VAO m_vao{};
    VBO m_vbo{};
    EBO m_ebo{};
};

export inline std::vector<glm::vec3> SpherePositions{};

export inline void AddSphere(glm::vec3 spawnSphere)
{
    SpherePositions.emplace_back(spawnSphere);
}