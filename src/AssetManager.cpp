#include "AssetManager.h"

AssetManager::AssetManager(EntityManager *manager) : manager(manager) {}

AssetManager::~AssetManager() {}

void AssetManager::clearData()
{
    textures.clear();
    fonts.clear();
}

void AssetManager::addTexture(std::string textureId, const char *filePath)
{
    textures.emplace(textureId, TextureManager::loadTexture(filePath));
}

SDL_Texture *AssetManager::getTexture(std::string textureId)
{
    return textures[textureId];
}

void AssetManager::addFont(std::string fontId, const char *filePath, int fontSize)
{
    fonts.emplace(fontId, FontManager::loadFont(filePath, fontSize));
}

TTF_Font *AssetManager::getFont(std::string fontId)
{
    return fonts[fontId];
}