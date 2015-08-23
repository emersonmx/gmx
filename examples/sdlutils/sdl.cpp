#include "sdlutils/sdl.hpp"


using namespace std;

namespace sdl {

void Timer::setup() {
    lastTicks = SDL_GetTicks();
}

float Timer::update() {
    Uint32 ticks = SDL_GetTicks();
    delta = (ticks - lastTicks) / 1000.f;
    lastTicks = ticks;
    return delta;
}

Window::Window(const string& title, int width, int height, Uint32 flags)
    : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
              width, height, flags) {}

Window::Window(const string& title, int x, int y, int width, int height, Uint32 flags) {
    window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    if (window == NULL) {
        throw sdl::Error();
    }
}

Renderer::Renderer(SDL_Window* window, Uint32 flags) {
    renderer = SDL_CreateRenderer(window, -1, flags);
    if (renderer == NULL) {
        throw Error();
    }
    setDrawColor(0, 0, 0, 0);
}

void Renderer::draw(Texture& texture, int x, int y) {
    SDL_Rect offset = { x, y, texture.getWidth(), texture.getHeight() };
    draw(texture, NULL, &offset);
}

void Renderer::draw(TextureRegion& region, int x, int y) {
    SDL_Rect offset = { x, y, region.getRegionWidth(), region.getRegionHeight() };
    SDL_Rect offsetSource = {
        region.getRegionX(), region.getRegionY(),
        region.getRegionWidth(), region.getRegionHeight()
    };

    draw(region.getTexture(), &offsetSource, &offset);
}

unique_ptr<Texture> loadTexture(SDL_Renderer* renderer, string filename) {
    SDL_Texture* sdltexture = IMG_LoadTexture(renderer, filename.c_str());
    if (sdltexture == NULL) {
        return NULL;
    }

    int w, h;
    SDL_QueryTexture(sdltexture, NULL, NULL, &w, &h);

    return unique_ptr<Texture>(new Texture(sdltexture, w, h));
}

} /* namespace sdl */
