module;
#include <stdexcept>
#include <string>
#include <utility>
#include <unordered_map>
#include <memory>
#include <glad/glad.h>
module ResourceManager;


std::unordered_map<std::string, std::unique_ptr<Shader>> ResourceManager::s_shaders{};
std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::s_textures{};

Shader& ResourceManager::LoadShader(std::string_view name,
                                    const char* vertexPath,
                                    const char* fragmentPath)
{
    if (auto it = s_shaders.find(std::string{name}); it != s_shaders.end())
    {
        return *it->second;
    }

    auto shader = std::make_unique<Shader>(vertexPath, fragmentPath);
    Shader& ref = *shader;
    s_shaders.emplace(std::string{name}, std::move(shader));
    return ref;
}

Texture& ResourceManager::LoadTexture(std::string_view name,
                                      const char* texturePath,
                                      GLenum texType,
                                      GLenum slot,
                                      GLenum pixelType,
                                      bool verticalEnable)
{
    if (auto it = s_textures.find(std::string{name}); it != s_textures.end())
    {
        return *it->second;
    }

    auto texture = std::make_unique<Texture>(
        texturePath,
        texType,
        slot,
        pixelType,
        verticalEnable
    );

    Texture& ref = *texture;
    s_textures.emplace(std::string{name}, std::move(texture));
    return ref;
}

Shader& ResourceManager::GetShader(std::string_view name)
{
    if (auto it = s_shaders.find(std::string{name}); it != s_shaders.end())
    {
        return *it->second;
    }

    throw std::runtime_error("Shader not found: " + std::string{name});
}

Texture& ResourceManager::GetTexture(std::string_view name)
{
    if (auto it = s_textures.find(std::string{name}); it != s_textures.end())
    {
        return *it->second;
    }

    throw std::runtime_error("Texture not found: " + std::string{name});
}

bool ResourceManager::HasShader(std::string_view name)
{
    return s_shaders.contains(std::string{name});
}

bool ResourceManager::HasTexture(std::string_view name)
{
    return s_textures.contains(std::string{name});
}

void ResourceManager::UnloadShader(std::string_view name)
{
    s_shaders.erase(std::string{name});
}

void ResourceManager::UnloadTexture(std::string_view name)
{
    s_textures.erase(std::string{name});
}

void ResourceManager::Clear()
{
    s_shaders.clear();
    s_textures.clear();
}