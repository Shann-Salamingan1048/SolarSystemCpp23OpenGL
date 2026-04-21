module;
#include <glad/glad.h>
#include <glm/glm.hpp>

export module Renderer;

import Shader;
import Sphere;

export struct Renderer
{

public:
    void DrawSphere(
        Shader& shader,
        Sphere& sphere,
        const glm::mat4& model,
        const glm::mat4& view,
        const glm::mat4& projection
    ) const;

    void DrawTexturedSphere(
        Shader& shader,
        Sphere& sphere,
        GLuint texture,
        const glm::mat4& model,
        const glm::mat4& view,
        const glm::mat4& projection
    ) const;
};