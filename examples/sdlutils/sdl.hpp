#ifndef SDL_UTILS_HPP
#define SDL_UTILS_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <memory>
#include <string>
#include <stdexcept>

#include "gmx/graphics.hpp"

namespace sdl {

class Error : public std::logic_error {
    public:
        Error() : logic_error(SDL_GetError()) {}
        Error(const std::string message) : logic_error(message) {}
        virtual ~Error() {}
};

class Texture : public gmx::Texture<SDL_Texture*> {
    public:
        Texture(SDL_Texture* texture, int width, int height)
            : gmx::Texture<SDL_Texture*>(texture, width, height) {}
        virtual ~Texture() {
            SDL_DestroyTexture(texture);
        }
};

class TextureRegion : public gmx::TextureRegion<SDL_Texture*> {
    public:
        TextureRegion(Texture& texture)
            : gmx::TextureRegion<SDL_Texture*>(texture) {}
        TextureRegion(Texture& texture, int x, int y, int w, int h)
            : gmx::TextureRegion<SDL_Texture*>(texture, x, y, w, h) {}
        virtual ~TextureRegion() {}
};

class Timer {
    public:
        Timer() : delta(0.f), lastTicks(0) {}
        virtual ~Timer() {}

        float getDelta() { return delta; }

        void setup();
        float update();

    private:
        float delta;
        Uint32 lastTicks;
};

class Window {
    public:
        Window(const std::string& title, int width, int height,
               Uint32 flags=SDL_WINDOW_HIDDEN);
        Window(const std::string& title, int x, int y, int width, int height,
               Uint32 flags=SDL_WINDOW_HIDDEN);
        virtual ~Window() {
            SDL_DestroyWindow(window);
        }

        std::string getTitle() {
            return SDL_GetWindowTitle(window);
        }
        void setTitle(const std::string& title) {
            SDL_SetWindowTitle(window, title.c_str());
        }

        void getSize(int* width, int* height) {
            return SDL_GetWindowSize(window, width, height);
        }
        void setSize(int width, int height) {
            SDL_SetWindowSize(window, width, height);
        }
        SDL_Surface* getSurface() {
            return SDL_GetWindowSurface(window);
        }

        void show() {
            SDL_ShowWindow(window);
        }
        void hide() {
            SDL_HideWindow(window);
        }
        void restore() {
            SDL_RestoreWindow(window);
        }
        void maximize() {
            SDL_MaximizeWindow(window);
        }
        void minimize() {
            SDL_MinimizeWindow(window);
        }
        int refresh() {
            return SDL_UpdateWindowSurface(window);
        }

        operator SDL_Window*() { return window; }

    protected:
        SDL_Window* window;
};

class Renderer {
    public:
        static const Uint32 DEFAULT_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

        Renderer(SDL_Window* window, Uint32 flags=DEFAULT_FLAGS);
        virtual ~Renderer() {
            SDL_DestroyRenderer(renderer);
        }

        void setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
            SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        }
        void draw(Texture& texture, int x, int y);
        void draw(TextureRegion& region, int x, int y);
        void draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* offset) {
            SDL_RenderCopy(renderer, texture, source, offset);
        }
        void clear() {
            SDL_RenderClear(renderer);
        }
        void present() {
            SDL_RenderPresent(renderer);
        }

        operator SDL_Renderer*() { return renderer; }

    private:
        SDL_Renderer* renderer;
};

std::unique_ptr<Texture> loadTexture(SDL_Renderer* renderer, std::string filename);

} /* namespace sdl */
#endif /* SDL_UTILS_HPP */
