#include "AssetManager.h"

AssetManager::AssetManager(EntityManager *manager) : manager(manager) {}

AssetManager::~AssetManager() {}

void AssetManager::clearData()
{
    textures.clear();
}

void AssetManager::addTexture(std::string textureId, const char *filePath)
{
    textures.emplace(textureId, TextureManager::loadTexture(filePath));
}

SDL_Texture *AssetManager::getTexture(std::string textureId)
{
    return textures[textureId];
}