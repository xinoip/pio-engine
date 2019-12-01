#include "TextureManager.h"

SDL_Texture *TextureManager::loadTexture(const char *fileName)
{
    SDL_Surface* surface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::draw(SDL_Texture *texture, SDL_Rect srcRectangle, SDL_Rect destRectangle, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &srcRectangle, &destRectangle, 0.0, NULL, flip);
}