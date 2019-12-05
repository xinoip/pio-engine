#ifndef _Collision_h_
#define _Collision_h_

#include <SDL2/SDL.h>

class Collision
{
public:
    static bool checkRectCollision(const SDL_Rect &rectA, const SDL_Rect &rectB);
};

#endif