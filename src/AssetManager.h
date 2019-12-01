#ifndef _Asset_Manager_h_
#define _Asset_Manager_h_

#include <map>
#include <string>
#include "TextureManager.h"
#include "EntityManager.h"

class AssetManager
{
private:
    EntityManager *manager;
    std::map<std::string, SDL_Texture *> textures;

public:
    AssetManager(EntityManager *manager);
    ~AssetManager();
    void clearData();
    void addTexture(std::string textureId, const char *filePath);
    SDL_Texture *getTexture(std::string textureId);
};

#endif