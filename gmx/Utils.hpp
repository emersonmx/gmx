#ifndef HELLO_GAME_UTILS_HPP
#define HELLO_GAME_UTILS_HPP

#include <SDL_render.h>

namespace gmx {

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);

}
#endif /* HELLO_GAME_UTILS_HPP */

