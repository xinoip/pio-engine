#ifndef _Map_h_
#define _Map_h_

#include <string>

class Map
{
private:
    std::string textureId;
    int scale;
    int tileSize;

public:
    Map(std::string textureId, int scale, int tileSize);
    ~Map();

    void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
    void addTile(int sourceX, int sourceY, int x, int y);
};

#endif