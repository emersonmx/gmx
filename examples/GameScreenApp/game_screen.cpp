#include <cstdio>
#include <cstdlib>

#include "gmx/game.hpp"
#include "gmx/default_screen.hpp"

using namespace std;

class GameScreenApp : public gmx::Game {
    protected:
        virtual void create() {
            printf("Created\n");
        }

        virtual void dispose() {
            printf("App disposed\n");
        }

    private:
};

class TestScreen : public gmx::DefaultScreen {
    public:
        TestScreen(GameScreenApp& game) : game(game), count(1) {}
        virtual ~TestScreen() {}

        virtual void show() {
            printf("Screen show\n");
        }

        virtual void hide() {
            printf("Screen hide\n");
        }

        virtual void update() {
            printf("Screen updated %d\n", count);
            if (count++ >= 10) {
                game.exit();
            }
        }

        virtual void dispose() {
            printf("Screen disposed\n");
        }

    private:
        GameScreenApp& game;
        int count;
};

int main() {
    GameScreenApp app;
    app.setScreen(std::make_shared<TestScreen>(app));
    return app.run();
}
