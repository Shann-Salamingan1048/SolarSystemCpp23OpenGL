#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_images.h>

#include <print>

Texture::Texture(
    const char* image,
    GLenum texType,
    GLenum texSlot,
    GLenum pixelType,
    bool verticalEnable
)
{
    init(image, texType, texSlot, pixelType, verticalEnable);
}

Texture::~Texture()
{
    Delete();
}

Texture::Texture(Texture&& other) noexcept
    : ID{other.ID},
      type{other.type},
      slot{other.slot}
{
    other.ID = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other)
    {
        Delete();

        ID = other.ID;
        type = other.type;
        slot = other.slot;

        other.ID = 0;
    }

    return *this;
}

void Texture::init(
    const char* image,
    GLenum texType,
    GLenum texSlot,
    GLenum pixelType,
    bool verticalEnable
)
{
    Delete();

    type = texType;
    slot = texSlot;

    std::println("Loading texture: {}", image);

    int widthImg = 0;
    int heightImg = 0;
    int numColCh = 0;

    stbi_set_flip_vertically_on_load(verticalEnable);

    unsigned char* bytes = stbi_load(
        image,
        &widthImg,
        &heightImg,
        &numColCh,
        0
    );

    if (bytes == nullptr)
    {
        std::println("Failed to load image: {}", image);
        std::println("stbi reason: {}", stbi_failure_reason());
        return;
    }

    GLenum imgFormat = GL_RGB;

    switch (numColCh)
    {
        case 1:
            imgFormat = GL_RED;
            break;

        case 3:
            imgFormat = GL_RGB;
            break;

        case 4:
            imgFormat = GL_RGBA;
            break;

        default:
            std::println(
                "Warning: unexpected channel count = {}, defaulting to GL_RGB",
                numColCh
            );
            imgFormat = GL_RGB;
            break;
    }

    glGenTextures(1, &ID);

    glActiveTexture(slot);
    glBindTexture(type, ID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        type,
        0,
        imgFormat,
        widthImg,
        heightImg,
        0,
        imgFormat,
        pixelType,
        bytes
    );

    glGenerateMipmap(type);

    glBindTexture(type, 0);

    stbi_image_free(bytes);

    std::println(
        "Texture loaded successfully: {} | size: {}x{} | channels: {} | ID: {}",
        image,
        widthImg,
        heightImg,
        numColCh,
        ID
    );
}

void Texture::setFilterTexture(GLint filter1, GLint filter2)
{
    if (ID == 0)
    {
        return;
    }

    glActiveTexture(slot);
    glBindTexture(type, ID);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, filter1);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, filter2);

    glBindTexture(type, 0);
}

void Texture::setFilterMipMap(GLint filter1, GLint filter2)
{
    if (ID == 0)
    {
        return;
    }

    glActiveTexture(slot);
    glBindTexture(type, ID);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, filter1);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, filter2);

    glBindTexture(type, 0);
}

void Texture::setActiveTexture(GLenum texSlot)
{
    slot = texSlot;
    glActiveTexture(slot);
}

void Texture::Bind() const
{
    if (ID == 0)
    {
        std::println("Texture::Bind failed. Texture ID is 0.");
        return;
    }

    glActiveTexture(slot);
    glBindTexture(type, ID);

}

void Texture::Unbind() const
{
    glBindTexture(type, 0);
}

void Texture::Delete() noexcept
{
    if (ID != 0)
    {
        glDeleteTextures(1, &ID);
        ID = 0;
    }
}