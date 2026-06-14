#pragma once

#include <cstdint>
#include <vector>

#include <glad/glad.h>

#include "BaseShape3D.hpp"

#include "../vao.hpp"
#include "../vbo.hpp"
#include "../ebo.hpp"

class Sphere final : public BaseShape3D
{
public:
    Sphere() = default;

    explicit Sphere(
        float radius,
        uint32_t sectors,
        uint32_t stacks
    );

    Sphere(
        uint16_t width,
        uint16_t height,
        uint16_t depth,
        float radius = 0.5f,
        uint32_t sectors = 36,
        uint32_t stacks = 18
    );

    ~Sphere() override;

    Sphere(const Sphere&) = delete;
    Sphere& operator=(const Sphere&) = delete;

    Sphere(Sphere&&) = delete;
    Sphere& operator=(Sphere&&) = delete;

    void Draw() override;

    void init(
        float radius = 0.5f,
        uint32_t sectors = 36,
        uint32_t stacks = 18
    );

    void init(
        uint16_t width,
        uint16_t height,
        uint16_t depth,
        float radius = 0.5f,
        uint32_t sectors = 36,
        uint32_t stacks = 18
    );

private:
    void BuildSphere(float radius, uint32_t sectors, uint32_t stacks);
    void SetupBuffers();
    void ReleaseBuffers();

private:
    std::vector<GLfloat> m_vertices;
    std::vector<GLuint> m_indices;

    GLsizei m_indexCount{0};

    VAO m_vao{};
    VBO m_vbo{};
    EBO m_ebo{};
};