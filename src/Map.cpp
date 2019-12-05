#include <fstream>
#include "Game.h"
#include "Map.h"
#include "EntityManager.h"
#include "Components/TileComponent.h"

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize)
{
    this->textureId = textureId;
    this->scale = scale;
    this->tileSize = tileSize;
}

Map::~Map()
{
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
{
    std::fstream mapFile;
    mapFile.open(filePath);

    for (int y = 0; y < mapSizeY; y++)
    {
        for (int x = 0; x < mapSizeX; x++)
        {
            char ch;
            mapFile.get(ch);
            int srcRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int srcRectX = atoi(&ch) * tileSize;
            addTile(srcRectX, srcRectY, x * (scale * tileSize), y * (scale * tileSize));
            mapFile.ignore();
        }
    }

    mapFile.close();
    // read map definitions from file
}

void Map::addTile(int sourceX, int sourceY, int x, int y)
{
    Entity& newTile(manager.addEntity("Tile", TILEMAP_LAYER));
    newTile.addComponent<TileComponent>(sourceX, sourceY, x, y, tileSize, scale, textureId);
}