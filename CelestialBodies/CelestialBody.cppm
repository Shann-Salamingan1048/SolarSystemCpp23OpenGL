module;
#include <glad/glad.h>
export module CelestialBody;
import Sphere;
import Shader;
import Texture;
// Hindi pa gets
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
    void setShader(const char* vertPath, const char* fragPath)
    {
        p_shader.init(vertPath, fragPath);
    }
    void setTexture(const char* image, GLenum texType, GLenum slot, GLenum pixelType, bool verticalEnable)
    {
        p_texture.init(image, texType, slot, pixelType, verticalEnable);
    }

    void initSphere(float radius, uint32_t sectors, uint32_t stacks)
    {
        p_sphere.init(radius, sectors, stacks);
    }
    void initSphere(uint16_t width, uint16_t height, uint16_t depth,
           float radius, uint32_t sectors, uint32_t stacks)
    {
        p_sphere.init(width, height, depth, radius, sectors, stacks);
    }

protected:
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

protected:
    [[nodiscard]] auto getEnableRevolution() const noexcept -> bool
    {
        return m_enableRevolution;
    }
    [[nodiscard]] auto getEnableRotation() const noexcept -> bool
    {
        return m_enableRotation;
    }
    [[nodiscard]] auto getVelocityRevolution() const noexcept -> float
    {
        return m_velocityRevolution;
    }
    [[nodiscard]] auto getVelocityRotation() const noexcept -> float
    {
        return m_velocityRotation;
    }

protected:
    Shader p_shader;
    Texture p_texture;
    Sphere p_sphere;

private:
    float m_velocityRevolution{0};
    float m_velocityRotation{0};
    bool m_enableRevolution{false};
    bool m_enableRotation{false};
};