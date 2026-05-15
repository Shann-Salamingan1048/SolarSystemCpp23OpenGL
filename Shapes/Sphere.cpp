#include "Sphere.hpp"

#include <cmath>
#include <numbers>
#include <print>

Sphere::~Sphere()
{
    ReleaseBuffers();
}

Sphere::Sphere(float radius, uint32_t sectors, uint32_t stacks)
{
    init(radius, sectors, stacks);
}

Sphere::Sphere(
    uint16_t width,
    uint16_t height,
    uint16_t depth,
    float radius,
    uint32_t sectors,
    uint32_t stacks
)
    : BaseShape3D{width, height, depth}
{
    init(radius, sectors, stacks);
}

void Sphere::init(float radius, uint32_t sectors, uint32_t stacks)
{
    BuildSphere(radius, sectors, stacks);
    SetupBuffers();
}

void Sphere::init(
    uint16_t width,
    uint16_t height,
    uint16_t depth,
    float radius,
    uint32_t sectors,
    uint32_t stacks
)
{
    size.width = width;
    size.height = height;
    size.depth = depth;

    BuildSphere(radius, sectors, stacks);
    SetupBuffers();
}

void Sphere::BuildSphere(float radius, uint32_t sectors, uint32_t stacks)
{
    m_vertices.clear();
    m_indices.clear();
    m_indexCount = 0;

    if (radius <= 0.0f || sectors < 3 || stacks < 2)
    {
        std::println(
            "Invalid sphere parameters: radius={}, sectors={}, stacks={}",
            radius,
            sectors,
            stacks
        );
        return;
    }

    const float pi = std::numbers::pi_v<float>;
    const float sectorStep = 2.0f * pi / static_cast<float>(sectors);
    const float stackStep = pi / static_cast<float>(stacks);

    for (uint32_t i = 0; i <= stacks; ++i)
    {
        const float stackAngle = pi / 2.0f - static_cast<float>(i) * stackStep;

        const float xy = radius * std::cos(stackAngle);
        const float z = radius * std::sin(stackAngle);

        const float v = static_cast<float>(i) / static_cast<float>(stacks);

        for (uint32_t j = 0; j <= sectors; ++j)
        {
            const float sectorAngle = static_cast<float>(j) * sectorStep;

            const float x = xy * std::cos(sectorAngle);
            const float y = xy * std::sin(sectorAngle);

            const float u = static_cast<float>(j) / static_cast<float>(sectors);

            const float nx = x / radius;
            const float ny = y / radius;
            const float nz = z / radius;

            // layout(location = 0): position
            m_vertices.push_back(x);
            m_vertices.push_back(y);
            m_vertices.push_back(z);

            // layout(location = 1): texture coordinates
            m_vertices.push_back(u);
            m_vertices.push_back(v);

            // layout(location = 2): normal
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

            if (i != stacks - 1)
            {
                m_indices.push_back(k1 + 1);
                m_indices.push_back(k2);
                m_indices.push_back(k2 + 1);
            }
        }
    }

    m_indexCount = static_cast<GLsizei>(m_indices.size());

    std::println("Sphere vertex float count: {}", m_vertices.size());
    std::println("Sphere index count: {}", m_indexCount);
}

void Sphere::SetupBuffers()
{
    if (m_vertices.empty() || m_indices.empty())
    {
        std::println("Sphere::SetupBuffers skipped: empty data.");
        return;
    }

    // If init() is called again, replace previous GPU data safely.
    m_vbo.SetData(
        m_vertices.data(),
        static_cast<GLsizeiptr>(m_vertices.size() * sizeof(GLfloat))
    );

    m_ebo.SetData(
        m_indices.data(),
        static_cast<GLsizeiptr>(m_indices.size() * sizeof(GLuint))
    );

    if (m_vao.ID == 0)
    {
        m_vao = VAO{};
    }

    constexpr GLsizeiptr stride = 8 * sizeof(GLfloat);

    // layout(location = 0) vec3 aPos;
    m_vao.LinkAttrib(
        m_vbo,
        0,
        3,
        GL_FLOAT,
        stride,
        reinterpret_cast<void*>(0)
    );

    // layout(location = 1) vec2 aTexCoords;
    m_vao.LinkAttrib(
        m_vbo,
        1,
        2,
        GL_FLOAT,
        stride,
        reinterpret_cast<void*>(3 * sizeof(GLfloat))
    );

    // layout(location = 2) vec3 aNormal;
    m_vao.LinkAttrib(
        m_vbo,
        2,
        3,
        GL_FLOAT,
        stride,
        reinterpret_cast<void*>(5 * sizeof(GLfloat))
    );

    // Important:
    // With your DSA VAO style, explicitly attach EBO to VAO.
    m_vao.LinkEBO(m_ebo);
}

void Sphere::ReleaseBuffers()
{
    m_ebo.Delete();
    m_vbo.Delete();
    m_vao.Delete();

    m_indexCount = 0;
}

void Sphere::Draw()
{
    if (m_vao.ID == 0 || m_indexCount <= 0)
    {
        std::println(
            "Sphere::Draw skipped. VAO={}, indexCount={}",
            m_vao.ID,
            m_indexCount
        );
        return;
    }

    m_vao.Bind();

    glDrawElements(
        GL_TRIANGLES,
        m_indexCount,
        GL_UNSIGNED_INT,
        nullptr
    );

    VAO::Unbind();
}