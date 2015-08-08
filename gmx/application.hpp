#ifndef GMX_APPLICATION_HPP
#define GMX_APPLICATION_HPP

#include <memory>

namespace gmx {

class Application {
    public:
        Application();
        virtual ~Application();

        int run();
        void exit(int errorCode=0);

    protected:
        virtual void create() = 0;
        virtual void dispose() = 0;
        virtual void update() = 0;

    private:
        bool running;
        int errorCode;
};

class Screen {
    public:
        virtual ~Screen() {}

        virtual void show() = 0;
        virtual void hide() = 0;
        virtual void update() = 0;
        virtual void dispose() = 0;
};

class DefaultScreen: public Screen {
    public:
        virtual ~DefaultScreen() {}

        virtual void show() {}
        virtual void hide() {}
        virtual void update() {}
        virtual void dispose() {}
};

class Game : public Application {
    public:
        typedef std::shared_ptr<Screen> ScreenPtr;

        Game();
        virtual ~Game();

        const ScreenPtr& getScreen() const;
        void setScreen(const ScreenPtr& screen);

        virtual void update();

    private:
        ScreenPtr screen;
};

} /* namespace gmx */
#endif /* GMX_APPLICATION_HPP */
