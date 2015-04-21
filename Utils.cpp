#include "Utils.hpp"

#include <SDL_image.h>

namespace gmx {

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filename);
    if (loadedSurface == NULL) {
        return NULL;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            return NULL;
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

}
