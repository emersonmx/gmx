#include "sdlutils/sdl.hpp"

#include <stdexcept>

using namespace std;

namespace sdl {

Error::Error()
    : logic_error(SDL_GetError()) {}

Error::Error(const string message) : logic_error(message) {}

Error::~Error() {}

Texture::Texture(SDL_Texture* texture, int width, int height)
    : gmx::Texture<SDL_Texture*>(texture, width, height) {}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

TextureRegion::TextureRegion() : gmx::TextureRegion<SDL_Texture*>() {}

TextureRegion::TextureRegion(Texture* texture)
    : gmx::TextureRegion<SDL_Texture*>(texture) {}

TextureRegion::~TextureRegion() {}

Timer::Timer()
    : delta(0.f), lastTicks(0) {}

Timer::~Timer() {}

float Timer::getDelta() {
    return delta;
}

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
    : Window (title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
              width, height, flags) {}

Window::Window(const string& title, int x, int y, int width, int height, Uint32 flags) {
    window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    if (window == NULL) {
        throw sdl::Error();
    }
}

Window::~Window() {
    SDL_DestroyWindow(window);
}

SDL_Window* Window::getSDLWindow() {
    return window;
}

string Window::getTitle() {
    return SDL_GetWindowTitle(window);
}

void Window::setTitle(const string& title) {
    SDL_SetWindowTitle(window, title.c_str());
}

void Window::getSize(int* width, int* height) {
    SDL_GetWindowSize(window, width, height);
}

void Window::setSize(int width, int height) {
    SDL_SetWindowSize(window, width, height);
}

SDL_Surface* Window::getSurface() {
    return SDL_GetWindowSurface(window);
}

void Window::show() {
    SDL_ShowWindow(window);
}

void Window::hide() {
    SDL_HideWindow(window);
}

void Window::restore() {
    SDL_RestoreWindow(window);
}

void Window::maximize() {
    SDL_MaximizeWindow(window);
}

void Window::minimize() {
    SDL_MinimizeWindow(window);
}

int Window::refresh() {
    return SDL_UpdateWindowSurface(window);
}

Renderer::Renderer(std::shared_ptr<Window>& window, Uint32 flags)
    : Renderer(*window, flags) {}

Renderer::Renderer(Window& window, Uint32 flags)
    : Renderer(window.getSDLWindow(), flags) {}

Renderer::Renderer(SDL_Window* window, Uint32 flags) {
    renderer = SDL_CreateRenderer(window, -1, flags);
    if (renderer == NULL) {
        throw Error();
    }
    setDrawColor(0, 0, 0, 0);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::draw(std::shared_ptr<Texture>& texture, int x, int y) {
    draw(texture.get(), x, y);
}

void Renderer::draw(Texture* texture, int x, int y) {
    SDL_Rect offset = { x, y, texture->getWidth(), texture->getHeight() };
    draw(*texture, NULL, &offset);
}

void Renderer::draw(std::shared_ptr<TextureRegion>& region, int x, int y) {
    draw(region.get(), x, y);
}

void Renderer::draw(TextureRegion* region, int x, int y) {
    SDL_Rect offset = { x, y, region->getRegionWidth(), region->getRegionHeight() };
    SDL_Rect offsetSource = {
        region->getRegionX(), region->getRegionY(),
        region->getRegionWidth(), region->getRegionHeight()
    };

    draw(*(region->getTexture()), &offsetSource, &offset);
}

void Renderer::draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* offset) {
    SDL_RenderCopy(renderer, texture, source, offset);
}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
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
