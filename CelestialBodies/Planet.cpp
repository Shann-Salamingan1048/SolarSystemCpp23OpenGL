module;
#include "glad/glad.h"
module Planet;
import DefaultValues;
void initPlanetTextures()
{
    // Diffuse
    ResourceManager::LoadTexture(SunDiffuse.name, SunDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(MercuryDiffuse.name, MercuryDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(VenusDiffuse.name, VenusDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(EarthDiffuse.name, EarthDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);

    ResourceManager::LoadTexture(MarsDiffuse.name, MarsDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(JupiterDiffuse.name, JupiterDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(SaturnDiffuse.name, SaturnDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(UranusDiffuse.name, UranusDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);
    ResourceManager::LoadTexture(NeptuneDiffuse.name, NeptuneDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE, true);

    // Specular
    ResourceManager::LoadTexture(EarthSpecular.name, EarthDiffuse.path, GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE, true);
}


