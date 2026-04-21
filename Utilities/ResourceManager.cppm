module;

#include <string>
#include <unordered_map>
#include <memory>
#include <glad/glad.h>
export module ResourceManager;

import Shader;
import Texture;

export class ResourceManager
{
public:
    ResourceManager() = delete;
    ~ResourceManager() = delete;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

public:
    static Shader& LoadShader(const std::string& name,
                              const char* vertexPath,
                              const char* fragmentPath);

    static Texture& LoadTexture(const std::string& name,
                                      const char* texturePath,
                                      GLenum texType, GLenum slot, GLenum pixelType, bool verticalEnable);

    static Shader& GetShader(const std::string& name);
    static Texture& GetTexture(const std::string& name);

    static bool HasShader(const std::string& name);
    static bool HasTexture(const std::string& name);

    static void UnloadShader(const std::string& name);
    static void UnloadTexture(const std::string& name);

    static void Clear();

private:
    static std::unordered_map<std::string, std::unique_ptr<Shader>> s_shaders;
    static std::unordered_map<std::string, std::unique_ptr<Texture>> s_textures;
};