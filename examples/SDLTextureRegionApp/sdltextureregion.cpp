#include <iostream>

#include "gmx/application.hpp"
#include "gmx/graphics.hpp"

#include "sdlutils/sdl.hpp"

#define WINDOW_TITLE "SDL TextureRegion Test"
#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240

using namespace std;

typedef shared_ptr<sdl::Window> WindowPtr;
typedef shared_ptr<sdl::Renderer> RendererPtr;
typedef shared_ptr<sdl::Texture> TexturePtr;
typedef shared_ptr<sdl::TextureRegion> TextureRegionPtr;

class SDLTextureRegionApp : public gmx::Application {
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

            timer.setup();
            count = 9;
            timeLapsed = 0.f;
        }

        bool initSDL() {
            Uint32 flags = SDL_INIT_VIDEO;
            return SDL_Init(flags) == 0;
        }

        bool createWindow() {
            try {
                window = make_shared<sdl::Window>(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
                window->show();
                return true;
            } catch (...) {}
            return false;
        }

        bool createRenderer() {
            try {
                renderer = make_shared<sdl::Renderer>();
                renderer->create(window.get());
                return true;
            } catch (...) {}
            return false;
        }

        bool initSDLImage() {
            Uint32 flags = IMG_INIT_PNG;
            if (!(IMG_Init(flags) & flags)) {
                return false;
            }
            return true;
        }

        bool loadAssets() {
            texture.reset(sdl::loadTexture(*renderer, "assets/numbers.png"));
            if (!texture) {
                return false;
            }
            return true;
        }

        virtual void dispose() {
            texture.reset();
            renderer.reset();
            window.reset();

            IMG_Quit();
            SDL_Quit();
        }

        virtual void update() {
            timer.update();
            handleInput();
            processLogic();
            draw();
        }

        void handleInput() {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    exit(0);
                }
            }
        }

        void processLogic() {
            timeLapsed += timer.getDelta();
            if (timeLapsed >= 1.f) {
                count--;
                timeLapsed = 0.f;
            }

            if (count < 0) {
                count = 0;
                cout << "BOOOOM!!!\n";
                exit(0);
            }

            region = make_shared<sdl::TextureRegion>(texture.get());
            region->setRegion(16*count, 0, 16, 16);
        }

        void draw() {
            renderer->clear();
            renderer->draw(region.get(),
                WINDOW_WIDTH / 2 - 8, WINDOW_HEIGHT / 2 - 8);
            renderer->present();
        }

        WindowPtr window;
        RendererPtr renderer;
        SDL_Event event;
        TexturePtr texture;
        TextureRegionPtr region;
        sdl::Timer timer;

        int count;
        float timeLapsed;
};

int main() {
    SDLTextureRegionApp app;
    return app.run();
}
