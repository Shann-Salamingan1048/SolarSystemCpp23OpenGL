#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>
#include <glad/glad.h>

class Shader;
class Texture;

class ResourceManager
{
public:
    ResourceManager() = delete;
    ~ResourceManager() = delete;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

public:
    static Shader& LoadShader(std::string_view name,
                              const char* vertexPath,
                              const char* fragmentPath);

    static Texture& LoadTexture(std::string_view name,
                                const char* texturePath,
                                GLenum texType,
                                GLenum slot,
                                GLenum pixelType,
                                bool verticalEnable);

    static Shader& GetShader(std::string_view name);
    static Texture& GetTexture(std::string_view name);

    static bool HasShader(std::string_view name);
    static bool HasTexture(std::string_view name);

    static void UnloadShader(std::string_view name);
    static void UnloadTexture(std::string_view name);

    static void Clear();

private:
    static std::unordered_map<std::string, std::unique_ptr<Shader>> s_shaders;
    static std::unordered_map<std::string, std::unique_ptr<Texture>> s_textures;
};