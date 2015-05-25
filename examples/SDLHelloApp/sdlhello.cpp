#include <cstdio>
#include <cstdlib>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "gmx/application.hpp"
#include "gmx/graphics.hpp"

using namespace std;

#define WINDOW_TITLE "SDL Hello"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Texture : public gmx::Texture {
    public:
        Texture(SDL_Texture* texture, int width, int height)
            : texture(texture), gmx::Texture(width, height) {}
        virtual ~Texture() {
            SDL_DestroyTexture(texture);
        }

        inline SDL_Texture* getTexture() { return texture; }

    private:
        SDL_Texture* texture;
};

typedef shared_ptr<Texture> TexturePtr;

SDL_Surface* loadImage(const char* filename) {
    SDL_Surface* loadedImage = IMG_Load(filename);
    if (loadedImage == NULL) {
        printf("Não foi possível carregar a image %s. IMG_Error: %s\n", filename, IMG_GetError());
        return NULL;
    }

    return loadedImage;
}

Texture* loadTexture(SDL_Renderer* renderer, const char* filename) {
    SDL_Surface* surface = loadImage(filename);
    if (surface == NULL) {
        return NULL;
    }

    int width=surface->w, height=surface->h;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Não foi possível criar a texture. SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(surface);

    return new Texture(texture, width, height);
}

class SDLHelloApp : public gmx::Application {
    public:
        SDLHelloApp() : window(NULL), renderer(NULL), texture(NULL) {}
        virtual ~SDLHelloApp() {}

    protected:
        virtual void create() {
            if (!initSDL()) {
                printf("A SDL não foi inicializada. SDL_Error: %s\n", SDL_GetError());
                exit(-1);
                return;
            }

            if (!createWindow()) {
                printf("Não foi possível criar a janela. SDL_Error: %s\n", SDL_GetError());
                exit(-1);
                return;
            }

            if (!createRenderer()) {
                printf("Não foi possível criar o renderer. SDL_Error: %s\n", SDL_GetError());
                exit(-1);
                return;
            }

            if (!initSDLImage()) {
                printf("Não foi possível iniciar a SDL_Image. IMG_Error: %s\n", IMG_GetError());
                exit(-1);
                return;
            }

            if (!loadAssets()) {
                printf("Não foi possível carregar as textures.\n");
                exit(-1);
                return;
            }
        }

        virtual void dispose() {
            texture.reset();

            IMG_Quit();

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        virtual void update() {
            handleInput();
            processLogic();
            draw();
        }

    protected:
        void handleInput() {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    exit(0);
                }
            }
        }

        void processLogic() {
        }

        void draw() {
            SDL_Rect offset;
            offset.x = offset.y = 0;
            offset.w = texture->getWidth();
            offset.h = texture->getHeight();

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture->getTexture(), NULL, &offset);
            SDL_RenderPresent(renderer);
        }

    private:
        bool initSDL() {
            Uint32 flags = SDL_INIT_VIDEO;
            return SDL_Init(flags) == 0;
        }

        bool createWindow() {
            Uint32 flags = SDL_WINDOW_SHOWN;
            int x=SDL_WINDOWPOS_UNDEFINED, y=SDL_WINDOWPOS_UNDEFINED;

            window = SDL_CreateWindow(WINDOW_TITLE, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, flags);
            return window != NULL;
        }

        bool createRenderer() {
            Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
            renderer = SDL_CreateRenderer(window, -1, flags);
            if (renderer == NULL) {
                return false;
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

            return true;
        }

        bool initSDLImage() {
            Uint32 flags = IMG_INIT_PNG;
            if (!(IMG_Init(flags) & flags)) {
                return false;
            }
            return true;
        }

        bool loadAssets() {
            Texture* texture = loadTexture(renderer, "assets/hello.png");
            if (texture == NULL) {
                return false;
            }

            this->texture.reset(texture);

            return true;
        }

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        TexturePtr texture;
};

int main(int argc, char* argv[]) {
    SDLHelloApp app;
    return app.run();
}
