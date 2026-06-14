#pragma once

#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

#include "../Shapes/Sphere.hpp" // Required because Sphere is stored by value

// Forward declarations are enough for pointers/references
class Shader;
class Texture;



class CelestialBody
{
public:
    CelestialBody() = default;
    virtual ~CelestialBody() = default;

    CelestialBody(const CelestialBody&) = delete;
    CelestialBody& operator=(const CelestialBody&) = delete;
    CelestialBody(CelestialBody&&) = delete;
    CelestialBody& operator=(CelestialBody&&) = delete;

    virtual void Draw() = 0;

protected:

    void setShader(Shader& shader) noexcept
    {
        p_shader = &shader;
    }

    void setTexture(const Texture& texture) noexcept
    {
        p_texture = &texture;
    }

    // If this CelestialBody owns its own sphere
    void initSphere(float radius, uint32_t sectors, uint32_t stacks)
    {
        p_sphere.init(radius, sectors, stacks);
    }

    void initSphere(
        uint16_t width,
        uint16_t height,
        uint16_t depth,
        float radius,
        uint32_t sectors,
        uint32_t stacks
    )
    {
        p_sphere.init(width, height, depth, radius, sectors, stacks);
    }

public:
    void setVelocityRevolution(float velocity) noexcept
    {
        m_velocityRevolution = velocity;
    }

    void setVelocityRotation(float velocity) noexcept
    {
        m_velocityRotation = velocity;
    }

    void setEnableRotation(bool enable) noexcept
    {
        m_enableRotation = enable;
    }

    void setEnableRevolution(bool enable) noexcept
    {
        m_enableRevolution = enable;
    }

public:
    [[nodiscard]] bool getEnableRevolution() const noexcept
    {
        return m_enableRevolution;
    }

    [[nodiscard]] bool getEnableRotation() const noexcept
    {
        return m_enableRotation;
    }

    [[nodiscard]] float getVelocityRevolution() const noexcept
    {
        return m_velocityRevolution;
    }

    [[nodiscard]] float getVelocityRotation() const noexcept
    {
        return m_velocityRotation;
    }

    [[nodiscard]] Shader& getShader() const
    {
        return *p_shader;
    }

    [[nodiscard]] const Texture& getTexture() const
    {
        return *p_texture;
    }

    [[nodiscard]] Sphere& getSphere()
    {
        return p_sphere;
    }

    [[nodiscard]] const Sphere& getSphere() const
    {
        return p_sphere;
    }

protected:
    Shader* p_shader{nullptr};         // non-owning pointer
    const Texture* p_texture{nullptr}; // non-owning pointer
    Sphere p_sphere{};                 // owned by CelestialBody

private:
    float m_velocityRevolution{0.0f};
    float m_velocityRotation{0.0f};
    bool m_enableRevolution{false};
    bool m_enableRotation{false};
};


