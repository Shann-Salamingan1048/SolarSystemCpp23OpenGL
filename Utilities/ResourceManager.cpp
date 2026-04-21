module;

#include <stdexcept>
#include <utility>
#include <memory>
module ResourceManager;

std::unordered_map<std::string, std::unique_ptr<Shader>> ResourceManager::s_shaders{};
std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::s_textures{};

Shader& ResourceManager::LoadShader(const std::string& name,
                                    const char* vertexPath,
                                    const char* fragmentPath)
{
    if (auto it = s_shaders.find(name); it != s_shaders.end())
    {
        return *it->second;
    }

    auto shader = std::make_unique<Shader>(vertexPath, fragmentPath);
    Shader& ref = *shader;
    s_shaders.emplace(name, std::move(shader));
    return ref;
}

Texture& ResourceManager::LoadTexture(const std::string& name,
                                      const char* texturePath,
                                      GLenum texType, GLenum slot, GLenum pixelType, bool verticalEnable)
{
    if (auto it = s_textures.find(name); it != s_textures.end())
    {
        return *it->second;
    }

    auto texture = std::make_unique<Texture>(texturePath, texType, slot, pixelType, verticalEnable);
    Texture& ref = *texture;
    s_textures.emplace(name, std::move(texture));
    return ref;
}

Shader& ResourceManager::GetShader(const std::string& name)
{
    if (auto it = s_shaders.find(name); it != s_shaders.end())
    {
        return *it->second;
    }

    throw std::runtime_error("Shader not found: " + name);
}

Texture& ResourceManager::GetTexture(const std::string& name)
{
    if (auto it = s_textures.find(name); it != s_textures.end())
    {
        return *it->second;
    }

    throw std::runtime_error("Texture not found: " + name);
}

bool ResourceManager::HasShader(const std::string& name)
{
    return s_shaders.contains(name);
}

bool ResourceManager::HasTexture(const std::string& name)
{
    return s_textures.contains(name);
}

void ResourceManager::UnloadShader(const std::string& name)
{
    s_shaders.erase(name);
}

void ResourceManager::UnloadTexture(const std::string& name)
{
    s_textures.erase(name);
}

void ResourceManager::Clear()
{
    s_shaders.clear();
    s_textures.clear();
}