#ifndef _Font_Manager_h_
#define _Font_Manager_h_

#include <SDL2/SDL_ttf.h>
#include "./Game.h"

class FontManager
{
public:
    static TTF_Font *loadFont(const char *fileName, int fontSize);
    static void draw(SDL_Texture* texture, SDL_Rect position);
};

#endif