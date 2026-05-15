#pragma once

#include <glad/glad.h>

class Texture
{
public:
    GLuint ID{0};
    GLenum type{GL_TEXTURE_2D};
    GLenum slot{GL_TEXTURE0};

public:
    Texture() = default;

    Texture(
        const char* image,
        GLenum texType,
        GLenum texSlot,
        GLenum pixelType,
        bool verticalEnable
    );

    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void init(
        const char* image,
        GLenum texType,
        GLenum texSlot,
        GLenum pixelType,
        bool verticalEnable
    );

    void setActiveTexture(GLenum texSlot);
    void setFilterMipMap(GLint filter1, GLint filter2);
    void setFilterTexture(GLint filter1, GLint filter2);

    void Bind() const;
    void Unbind() const;
    void Delete() noexcept;
};