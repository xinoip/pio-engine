#ifndef _Texture_Manager_h_
#define _Texture_Manager_h_

#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture *loadTexture(const char *fileName);
    static void draw(SDL_Texture* texture, SDL_Rect srcRectangle, SDL_Rect destRectangle, SDL_RendererFlip flip);
};

#endif