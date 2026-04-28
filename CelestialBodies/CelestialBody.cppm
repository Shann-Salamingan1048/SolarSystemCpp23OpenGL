module;
#include <glad/glad.h>
#include <cstdint>

export module CelestialBody;

import Sphere;
import Shader;
import Texture;

export class CelestialBody
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
    // ResourceManager-owned shader
    void setShader(Shader& shader) noexcept
    {
        p_shader = &shader;
    }

    // ResourceManager-owned texture
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

    [[nodiscard]] auto getShader() -> Shader&
    {
        return *p_shader;
    }
    [[nodiscard]] auto getTexture() -> const Texture&
    {
        return *p_texture;
    }
    [[nodiscard]] auto getSphere() -> Sphere&
    {
        return p_sphere;
    }
    [[nodiscard]] auto getSphere() const -> const Sphere&
    {
        return p_sphere;
    }

protected:
    Shader* p_shader{};              // non-const: for use(), uniforms, setMat4(), etc.
    const Texture* p_texture{};      // const: CelestialBody only uses/binds it
    Sphere p_sphere{};               // owned by CelestialBody

private:
    float m_velocityRevolution{0.0f};
    float m_velocityRotation{0.0f};
    bool m_enableRevolution{false};
    bool m_enableRotation{false};
};