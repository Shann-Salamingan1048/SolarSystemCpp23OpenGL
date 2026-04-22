module;
#include <print>
#include <cmath>
#include <numbers>
#include <glad/glad.h>

module Sphere;

Sphere::~Sphere()
{
    std::println("Sphere Destructor!");
    ReleaseBuffers();
}

Sphere::Sphere(float radius, uint32_t sectors, uint32_t stacks)
{
    init(radius, sectors, stacks);
}

Sphere::Sphere(uint16_t width, uint16_t height, uint16_t depth,
               float radius, uint32_t sectors, uint32_t stacks)
    : BaseShape3D{width, height, depth}
{
    init(radius, sectors, stacks);
}

void Sphere::init(float radius, uint32_t sectors, uint32_t stacks)
{
    ReleaseBuffers();
    BuildSphere(radius, sectors, stacks);
    SetupBuffers();
}

void Sphere::init(uint16_t width, uint16_t height, uint16_t depth,
                  float radius, uint32_t sectors, uint32_t stacks)
{
    size.width = width;
    size.depth = depth;
    size.height = height;

    ReleaseBuffers();
    BuildSphere(radius, sectors, stacks);
    SetupBuffers();
}

void Sphere::SetupBuffers()
{
    m_vao.Bind();
    m_vbo.Bind();
    m_ebo.Bind();

    m_vao.LinkAttrib(m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    m_vao.LinkAttrib(m_vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    m_vao.LinkAttrib(m_vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    m_vao.Unbind();
    m_vbo.Unbind();
    m_ebo.Unbind();
}

void Sphere::ReleaseBuffers()
{
    m_vao.Delete();
    m_vbo.Delete();
    m_ebo.Delete();
    m_indexCount = 0;
}

void Sphere::BuildSphere(float radius, uint32_t sectors, uint32_t stacks)
{
    m_vertices.clear();
    m_indices.clear();
    m_indexCount = 0;

    if (radius <= 0.0f || sectors < 3 || stacks < 2)
    {
        return;
    }

    const float pi = std::numbers::pi_v<float>;
    const float sectorStep = 2.0f * pi / static_cast<float>(sectors);
    const float stackStep  = pi / static_cast<float>(stacks);

    for (uint32_t i = 0; i <= stacks; ++i)
    {
        const float stackAngle = pi / 2.0f - static_cast<float>(i) * stackStep;
        const float xy = radius * std::cos(stackAngle);
        const float z  = radius * std::sin(stackAngle);
        const float v  = static_cast<float>(i) / static_cast<float>(stacks);

        for (uint32_t j = 0; j <= sectors; ++j)
        {
            const float sectorAngle = static_cast<float>(j) * sectorStep;

            const float x = xy * std::cos(sectorAngle);
            const float y = xy * std::sin(sectorAngle);
            const float u = static_cast<float>(j) / static_cast<float>(sectors);

            const float nx = x / radius;
            const float ny = y / radius;
            const float nz = z / radius;

            m_vertices.push_back(x);
            m_vertices.push_back(y);
            m_vertices.push_back(z);

            m_vertices.push_back(u);
            m_vertices.push_back(v);

            m_vertices.push_back(nx);
            m_vertices.push_back(ny);
            m_vertices.push_back(nz);
        }
    }

    for (uint32_t i = 0; i < stacks; ++i)
    {
        uint32_t k1 = i * (sectors + 1);
        uint32_t k2 = k1 + sectors + 1;

        for (uint32_t j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                m_indices.push_back(k1);
                m_indices.push_back(k2);
                m_indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                m_indices.push_back(k1 + 1);
                m_indices.push_back(k2);
                m_indices.push_back(k2 + 1);
            }
        }
    }

    m_indexCount = static_cast<GLsizei>(m_indices.size());

    m_vbo = VBO(
        m_vertices.data(),
        static_cast<GLsizeiptr>(m_vertices.size() * sizeof(GLfloat))
    );

    m_ebo = EBO(
        m_indices.data(),
        static_cast<GLsizeiptr>(m_indices.size() * sizeof(GLuint))
    );
}

void Sphere::Draw()
{
    m_vao.Bind();
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    m_vao.Unbind();
}