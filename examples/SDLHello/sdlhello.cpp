#include <cstdio>
#include <cstdlib>

#include "gmx/application.hpp"
#include "gmx/graphics.hpp"

using namespace std;

#define WINDOW_TITLE "SDL Hello"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class SDLHelloApp : public gmx::Application {
    public:
        SDLHelloApp() {}
        virtual ~SDLHelloApp() {}

    protected:
        virtual void create() {
        }

        virtual void dispose() {
        }

        virtual void update() {
        }

    private:
};

int main(int argc, char* argv[]) {
    SDLHelloApp app;
    return app.run();
}
